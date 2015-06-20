#include "IndexBuffer.h"
#include "../Infrastructure/Engine.h"
#include "GPUException.h"
#include <exception>

using namespace std;
using namespace Break::GXWrapper;
using namespace Break::Infrastructure;


IndexBuffer::IndexBuffer(Buffer::Type t){
	_type = t;
	if(_type == Buffer::DYNAMIC)
		_buffer = make_shared<RAMBuffer>(Buffer::DYNAMIC_OPTIMAL_SIZE);
	else if(_type == Buffer::STATIC)
		_buffer = make_shared<RAMBuffer>(Buffer::STATIC_OPTIMAL_SIZE);

	_changed = true;
	createGPUBuffer();
}

IndexBuffer::IndexBuffer(ISet* set,Buffer::Type t){
	_type = t;
	_buffer = set->getData();
	_changed = true;
	createGPUBuffer();
}

IndexBuffer::IndexBuffer(RAMBufferPtr buffer,Buffer::Type t){
	_type = t;
	_buffer = buffer;
	_changed = true;
	createGPUBuffer();
}

IndexBuffer::IndexBuffer(unsigned int size,Buffer::Type t){
	_type = t;
	_buffer = RAMBufferPtr(new RAMBuffer(size));
	_changed = true;
	createGPUBuffer();
}

IndexBuffer::IndexBuffer(const IndexBuffer& val):Buffer(val){
	_type = val._type;
}

IndexBuffer::~IndexBuffer(){
	Infrastructure::Engine::Instance->GraphicsDevice->deleteBuffer(this);
}

bool IndexBuffer::append(ISet* set){
	return _buffer->append(set->getData());
}

bool IndexBuffer::createGPUBuffer(){
	bool res = Engine::Instance->GraphicsDevice->createIndexBuffer(this);

	if(res)
		return res;
	else
		throw GPUException("Cannot create Index Buffer");
}

bool IndexBuffer::updateBuffer(unsigned int offset, unsigned int size){
	return Engine::Instance->GraphicsDevice->updateIndexBuffer(this,offset,size);
}