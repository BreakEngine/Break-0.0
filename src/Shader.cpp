#include "Shader.h"
#include "Engine.h"
#include "UniformBuffer.h"
#include "Texture.h"
#include <Texture2D.h>
#include <Services.h>
using namespace Break::GXWrapper;
using namespace std;

Shader::Shader(string vs,string ps,MemoryLayout inputLayout):_vs(vs),_ps(ps),_inputLayout(inputLayout){
	_type = Assets::IAsset::SHADER;
	createGPUResource();
	_vs.clear();
	_ps.clear();
}

Shader::Shader(const Shader& val):GPUResource(val){
	_type = Assets::IAsset::SHADER;
	_inputLayout=val._inputLayout;
	_uniformBlocks = val._uniformBlocks;
	_uniformsTable = val._uniformsTable;
	_samplersTable = val._samplersTable;

	_vs = val._vs;
	_ps = val._ps;
}

Shader::~Shader(){
	//Break::Infrastructure::Engine::Instance->GraphicsDevice->deleteShader(this);
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::DEL;

	ins.args.push(Renderer::GPU_ISA::PROGRAM);
	ins.args.push(_handle.get());

	Services::getGPU_VM()->execute(ins);

	if(_uniformsTable.size()>0)
		_uniformsTable.clear();
	if(_uniformBlocks.size()>0)
		_uniformBlocks.clear();
	if(_samplersTable.size()>0)
		_samplersTable.clear();
	if(_vs.size()>0)
		_vs.clear();
	if(_ps.size()>0)
		_ps.clear();
}

void Shader::use(){
	//engine->graphicsDevice->use();
	//Break::Infrastructure::Engine::Instance->GraphicsDevice->useShader(this);
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::BIND;

	ins.args.push(Renderer::GPU_ISA::PROGRAM);
	ins.args.push(_handle.get());

	Services::getGPU_VM()->execute(ins);
	flushUniforms();
}

void Shader::setUniform(string name, void* ptr){
	//set uniform
	auto uniform = _uniformsTable[name];
	_uniformBlocks[uniform._blockName]->map(ptr,uniform._size,uniform._offset);
}

void Shader::setTexture(std::string sampler, Texture* tex)
{
	auto sRow = _samplersTable[sampler];
	if(tex->sampler != sRow._state.get()){
		Break::Infrastructure::Engine::Instance->GraphicsDevice->applySamplerStateToTexture2D(sRow._state.get(),tex);
		Renderer::GPUIns ins;
		ins.instruction = Renderer::GPU_ISA::APPLY;
		ins.args.push(Renderer::GPU_ISA::SAMPLER);
		ins.args.push(Renderer::GPU_ISA::TEXTURE2D);
		ins.args.push(sRow._state->getHandle());
		ins.args.push(tex->getHandle());
		ins.args.push(tex->usingMipMaps());
		ins.args.push(sRow._state->addressU);
		ins.args.push(sRow._state->addressV);
		ins.args.push(sRow._state->filter);
		ins.args.push(sRow._state->compareFunction);
		ins.args.push(&sRow._state->borderColor);

		Services::getGPU_VM()->execute(ins);
		tex->sampler = sRow._state.get();
	}

	//Break::Infrastructure::Engine::Instance->GraphicsDevice->useSamplerState(sRow._state.get(),sRow._slot,(Shader::Type)sRow._shader);
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::BIND;
	ins.args.push(Renderer::GPU_ISA::SAMPLER);
	ins.args.push(sRow._state->getHandle());
	if(sRow._shader == VERTEX)
		ins.args.push(Renderer::GPU_ISA::VERTEX_SHADER);
	else if(sRow._shader == PIXEL)
		ins.args.push(Renderer::GPU_ISA::PIXEL_SHADER);
	ins.args.push(sRow._slot);
	Services::getGPU_VM()->execute(ins);

	tex->use((Shader::Type)sRow._shader,sRow._slot);
}

bool Shader::createGPUResource(){
	//engine->graphicsDevice->create();
	//return Break::Infrastructure::Engine::Instance->GraphicsDevice->createShader(this);
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::GEN;

	ins.args.push(Renderer::Arg(Renderer::GPU_ISA::PROGRAM));
	ins.args.push(Renderer::Arg(&_vs));
	ins.args.push(Renderer::Arg(&_ps));
	ins.args.push(Renderer::Arg(&_inputLayout));

	_handle = Services::getGPU_VM()->execute(ins);
	return true;
}

void Shader::registerUniform(std::string name,std::string blockName,unsigned int offset, unsigned int size){
	uniformRow var;
	var._blockName = blockName;
	var._size = size;
	var._offset = offset;
	_uniformsTable[name] = var;
}

void Shader::registerSampler(std::string name, unsigned slot, SamplerStatePtr state,Shader::Type shader)
{
	samplersRow var;
	var._state = state;
	var._shader = shader;
	var._slot = slot;
	//Break::Infrastructure::Engine::Instance->GraphicsDevice->createSamplerState(state.get());
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::GEN;
	ins.args.push(Renderer::GPU_ISA::SAMPLER);
	ins.args.push(state->addressU);
	ins.args.push(state->addressV);
	ins.args.push(state->addressW);
	ins.args.push(state->filter);
	ins.args.push(state->compareFunction);
	ins.args.push(&state->borderColor);
	state->setHandle(Services::getGPU_VM()->execute(ins));
	_samplersTable[name] = var;
}

void Shader::flushUniforms()
{
	for(auto& buffer : _uniformBlocks){
		buffer.second->invokeUpdate();
		buffer.second->use();
	}
}

void Shader::registerUniformBlock(std::string name,unsigned int size,unsigned int slot,Shader::Type shader){
	_uniformBlocks[name] = make_shared<UniformBuffer>(size,slot,shader);
}

std::string Shader::getVertexShader(){
	return _vs;
}

std::string Shader::getPixelShader(){
	return _ps;
}

MemoryLayout Shader::getInputLayout(){
	return _inputLayout;
}