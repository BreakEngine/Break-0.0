#include "VertexBuffer.h"
#include "Engine.h"
#include "GPUException.h"
#include <exception>

using namespace std;
using namespace Break::GXWrapper;
using namespace Break::Infrastructure;


VertexBuffer::VertexBuffer(Buffer::Type t,MemoryLayout& layout){
	_type = t;
	_layout = layout;
	if(_type == Buffer::DYNAMIC)
		_buffer = make_shared<RAMBuffer>(Buffer::DYNAMIC_OPTIMAL_SIZE);
	else if(_type == Buffer::STATIC)
		_buffer = make_shared<RAMBuffer>(Buffer::STATIC_OPTIMAL_SIZE);

	_changed = true;
}

VertexBuffer::VertexBuffer(ISet* set,MemoryLayout& layout,Buffer::Type t){
	_type = t;
	_layout = layout;
	_buffer = set->getData();
	_changed = true;
	createGPUResource();
}

VertexBuffer::VertexBuffer(RAMBufferPtr buffer, MemoryLayout& layout,Buffer::Type t){
	_type = t;
	_buffer = buffer;
	_layout = layout;
	_changed = true;
	createGPUResource();
}

VertexBuffer::VertexBuffer(unsigned int size,Buffer::Type t){
	_type = t;
	_buffer = RAMBufferPtr(new RAMBuffer(size));
	_changed = true;
}

VertexBuffer::VertexBuffer(const VertexBuffer& val):Buffer(val){
	_type = val._type;
	_layout = val._layout;
}

VertexBuffer::~VertexBuffer(){
	Infrastructure::Engine::Instance->GraphicsDevice->deleteBuffer(this);
}

bool VertexBuffer::append(ISet* set){
	return _buffer->append(set->getData());
}

bool VertexBuffer::createGPUResource(){
	bool res = Engine::Instance->GraphicsDevice->createVertexBuffer(this);

	if(res)
		return true;
	else
		throw GPUException("Cannot create Vertex Buffer");
}

bool VertexBuffer::updateBuffer(unsigned int offset, unsigned int size){
	return Engine::Instance->GraphicsDevice->updateVertexBuffer(this,offset,size);
}

void VertexBuffer::use(){
	Engine::Instance->GraphicsDevice->useVertexBuffer(this);
}

void VertexBuffer::setLayout(MemoryLayout& layout){
	_layout = layout;
}

MemoryLayout VertexBuffer::getLayout(){
	return _layout;
}