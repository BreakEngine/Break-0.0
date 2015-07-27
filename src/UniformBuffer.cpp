#include "UniformBuffer.h"
#include "Engine.h"
#include <memory>
using namespace Break::GXWrapper;
using namespace Break::Infrastructure;
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
	Engine::Instance->GraphicsDevice->deleteBuffer(this);
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
		Engine::Instance->GraphicsDevice->updateUniformBuffer(this,0,getSize());
		needUpdate = false;
	}
}

bool UniformBuffer::appendBuffer(void* data,unsigned int size){
	return _buffer->append(data,size);
}

void UniformBuffer::flush(){
	if(!_handle)
		Engine::Instance->GraphicsDevice->createUniformBuffer(this);
	else
		Engine::Instance->GraphicsDevice->updateUniformBuffer(this,0,_buffer->getSize());
}

bool UniformBuffer::createGPUResource(){
	Engine::Instance->GraphicsDevice->createUniformBuffer(this);
	return true;
}

void UniformBuffer::use(){
	Engine::Instance->GraphicsDevice->useUniformBuffer(this);
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