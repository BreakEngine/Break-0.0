#include "Shader.h"
#include "Engine.h"
#include "UniformBuffer.h"
#include "Texture.h"
#include <Texture2D.h>
using namespace Break::GXWrapper;
using namespace std;

Shader::Shader(string vs,string ps,MemoryLayout& inputLayout):_vs(vs),_ps(ps),_inputLayout(inputLayout){
	createGPUResource();
	_vs.clear();
	_ps.clear();
}

Shader::Shader(const Shader& val):GPUResource(val){

}

Shader::~Shader(){
	Break::Infrastructure::Engine::Instance->GraphicsDevice->deleteShader(this);
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
	for(auto& buffer : _uniformBlocks){
		buffer.second->invokeUpdate();
		buffer.second->use();
	}
	Break::Infrastructure::Engine::Instance->GraphicsDevice->useShader(this);
}

void Shader::setUniform(string name, void* ptr){
	//set uniform
	auto uniform = _uniformsTable[name];
	_uniformBlocks[uniform._blockName]->map(ptr,uniform._size,uniform._offset);
}

void Shader::setTexture(std::string sampler, Texture* tex)
{
	Break::Infrastructure::Engine::Instance->GraphicsDevice->applySamplerStateToTexture2D(_samplersTable[sampler]._state.get(),tex);

	auto sRow = _samplersTable[sampler];
	Break::Infrastructure::Engine::Instance->GraphicsDevice->useSamplerState(sRow._state.get(),sRow._slot,(Shader::Type)sRow._shader);
	if(tex->getType() == Texture::TEXTURE2D)
	{
		Texture2D* tex2D = dynamic_cast<Texture2D*>(tex);
		tex2D->use((Shader::Type)sRow._shader,sRow._slot);
	}
}

bool Shader::createGPUResource(){
	//engine->graphicsDevice->create();
	return Break::Infrastructure::Engine::Instance->GraphicsDevice->createShader(this);
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
	Break::Infrastructure::Engine::Instance->GraphicsDevice->createSamplerState(state.get());
	_samplersTable[name] = var;
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