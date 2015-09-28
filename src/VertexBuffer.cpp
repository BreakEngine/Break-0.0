#include "VertexBuffer.h"
#include "Engine.h"
#include "GPUException.h"
#include "GPU_ISA.hpp"
#include <exception>
#include <Services.h>

using namespace std;
using namespace Break::GXWrapper;
using namespace Break::Infrastructure;


VertexBuffer::VertexBuffer(Buffer::Type t,MemoryLayout layout){
	_type = t;
	_layout = layout;
	if(_type == Buffer::DYNAMIC)
		_buffer = make_shared<RAMBuffer>(Buffer::DYNAMIC_OPTIMAL_SIZE);
	else if(_type == Buffer::STATIC)
		_buffer = make_shared<RAMBuffer>(Buffer::STATIC_OPTIMAL_SIZE);

	_changed = true;
	createGPUResource();
}

VertexBuffer::VertexBuffer(ISet* set,MemoryLayout layout,Buffer::Type t){
	_type = t;
	_layout = layout;
	_buffer = set->getData();
	_changed = true;
	createGPUResource();
}

VertexBuffer::VertexBuffer(RAMBufferPtr buffer, MemoryLayout layout,Buffer::Type t){
	_type = t;
	_buffer = buffer;
	_layout = layout;
	_changed = true;
	createGPUResource();
}

VertexBuffer::VertexBuffer(const VertexBuffer& val):Buffer(val){
	_type = val._type;
	_layout = val._layout;
}

VertexBuffer::~VertexBuffer(){
	//Infrastructure::Engine::Instance->GraphicsDevice->deleteBuffer(this);
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::DEL;
	ins.args.push(Renderer::Arg(Renderer::GPU_ISA::VERTEX_BUFFER));
	ins.args.push(Renderer::Arg(_handle.get()));

	Services::getGPU_VM()->execute(ins);
}

bool VertexBuffer::append(ISet* set){
	return _buffer->append(set->getData().get());
}

bool VertexBuffer::createGPUResource(){
	/*
	bool res = Engine::Instance->GraphicsDevice->createVertexBuffer(this);

	if(res)
		return true;
	else
		throw GPUException("Cannot create Vertex Buffer");
		*/

	Break::Renderer::GPUIns ins;
	ins.instruction = Break::Renderer::GPU_ISA::GEN;
	ins.args.push(Break::Renderer::Arg(Renderer::GPU_ISA::VERTEX_BUFFER));
	if(_type == Type::STATIC)
		ins.args.push(Break::Renderer::Arg(Renderer::GPU_ISA::STATIC));
	else if(_type == Type::DYNAMIC)
		ins.args.push(Break::Renderer::Arg(Renderer::GPU_ISA::DYNAMIC));
	ins.args.push(Break::Renderer::Arg(_buffer->getSize()));
	ins.args.push(Break::Renderer::Arg(_buffer->getData()));

	try{
		_handle = Services::getGPU_VM()->execute(ins);
	}catch(GPUException e)
	{
		cerr<<e.what()<<endl;
		return false;
	}

	return true;
}

bool VertexBuffer::updateBuffer(unsigned int offset, unsigned int size){
	//return Engine::Instance->GraphicsDevice->updateVertexBuffer(this,offset,size);
	if(_type == Type::STATIC)
		throw GPUException("Cannot Map Vertex Buffer: Buffer type is not dynamic");

	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::MAP;
	ins.args.push(Renderer::Arg(Renderer::GPU_ISA::VERTEX_BUFFER));
	ins.args.push(Renderer::Arg(_handle.get()));
	ins.args.push(Renderer::Arg(_buffer->getSize()));
	ins.args.push(Renderer::Arg(_buffer->getData()));

	Services::getGPU_VM()->execute(ins);
	return true;
}

void VertexBuffer::use(){
	//Engine::Instance->GraphicsDevice->useVertexBuffer(this);
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::BIND;
	ins.args.push(Renderer::Arg(Renderer::GPU_ISA::VERTEX_BUFFER));
	ins.args.push(Renderer::Arg(_handle.get()));
	ins.args.push(Renderer::Arg(getLayout().getSize()));

	Services::getGPU_VM()->execute(ins);
}

void VertexBuffer::setLayout(MemoryLayout& layout){
	_layout = layout;
}

MemoryLayout VertexBuffer::getLayout(){
	return _layout;
}