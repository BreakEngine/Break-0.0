#include "UniformBuffer.h"
#include "Engine.h"
#include <memory>
#include <Services.h>
#include <GPUException.h>
using namespace Break::GXWrapper;
using namespace Break::Infrastructure;
using namespace Break;
using namespace std;

UniformBuffer::UniformBuffer(){
	_buffer = nullptr;
	_slot = 0;
	needUpdate = false;
}
UniformBuffer::UniformBuffer(const UniformBuffer& val):GPUResource(val){
	_buffer = val._buffer;
	needUpdate = false;
}

UniformBuffer::UniformBuffer(unsigned int size,unsigned int slot,Shader::Type shader){
	_buffer = make_shared<RAMBuffer>(size);
	_slot = slot;
	_shader = shader;
	needUpdate = false;
	createGPUResource();
}

UniformBuffer::~UniformBuffer(){
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::DEL;
	ins.args.push(Renderer::Arg(Renderer::GPU_ISA::UNIFORM_BUFFER));
	ins.args.push(Renderer::Arg(_handle.get()));

	Services::getGPU_VM()->execute(ins);
	if(_buffer)
		_buffer = nullptr;
}

void UniformBuffer::clear(){
	_buffer->clear();
	needUpdate = true;
}

void UniformBuffer::reallocate(unsigned int size){
	_buffer->reallocate(size);
	//to be managed later
}

void UniformBuffer::map(void* data,unsigned int size, unsigned int start){
	_buffer->map(data,size,start);
	//Engine::Instance->GraphicsDevice->updateUniformBuffer(this,start,size);
	needUpdate = true;
}

void UniformBuffer::invokeUpdate()
{
	if(needUpdate){
		Renderer::GPUIns ins;
		ins.instruction = Renderer::GPU_ISA::MAP;
		ins.args.push(Renderer::Arg(Renderer::GPU_ISA::UNIFORM_BUFFER));
		ins.args.push(Renderer::Arg(_handle.get()));
		ins.args.push(Renderer::Arg(_buffer->getSize()));
		ins.args.push(Renderer::Arg(_buffer->getData()));
		
		Services::getGPU_VM()->execute(ins);
		needUpdate = false;
	}
}

bool UniformBuffer::appendBuffer(void* data,unsigned int size){
	return _buffer->append(data,size);
}

void UniformBuffer::flush(){
	if(!_handle)
		createGPUResource();
	else{
		//Engine::Instance->GraphicsDevice->updateUniformBuffer(this,0,_buffer->getSize());
		Renderer::GPUIns ins;
		ins.instruction = Renderer::GPU_ISA::MAP;
		ins.args.push(Renderer::Arg(Renderer::GPU_ISA::UNIFORM_BUFFER));
		ins.args.push(Renderer::Arg(_handle.get()));
		ins.args.push(Renderer::Arg(_buffer->getSize()));
		ins.args.push(Renderer::Arg(_buffer->getData()));
		
		Services::getGPU_VM()->execute(ins);
	}
}

bool UniformBuffer::createGPUResource(){
	//Engine::Instance->GraphicsDevice->createUniformBuffer(this);
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::GEN;
	ins.args.push(Renderer::Arg(Renderer::GPU_ISA::UNIFORM_BUFFER));
	ins.args.push(Renderer::Arg(_buffer->getSize()));
	ins.args.push(Renderer::Arg(_buffer->getData()));
	ins.args.push(Renderer::Arg(_slot));

	try{
		_handle = Services::getGPU_VM()->execute(ins);
	}catch(GPUException e)
	{
		cerr<<e.what()<<endl;
		return false;
	}
	return true;
}

void UniformBuffer::use(){
	//Engine::Instance->GraphicsDevice->useUniformBuffer(this);
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::BIND;
	ins.args.push(Renderer::Arg(Renderer::GPU_ISA::UNIFORM_BUFFER));
	ins.args.push(Renderer::Arg(_handle.get()));
	if(_shader == Shader::VERTEX)
		ins.args.push(Renderer::Arg(Renderer::GPU_ISA::VERTEX_SHADER));
	else if(_shader == Shader::PIXEL)
		ins.args.push(Renderer::Arg(Renderer::GPU_ISA::PIXEL_SHADER));

	ins.args.push(Renderer::Arg(_slot));

	try{
		Services::getGPU_VM()->execute(ins);
	}catch(GPUException e)
	{
		cerr<<e.what()<<endl;
	}
}

unsigned int UniformBuffer::getSlot(){
	return _slot;
}

void UniformBuffer::setSlot(unsigned int val){
	_slot = val;
}

unsigned int UniformBuffer::getSize(){
	return _buffer->getSize();
}

byte* UniformBuffer::getData(unsigned int offset/* =0 */){
	return _buffer->getData(offset);
}