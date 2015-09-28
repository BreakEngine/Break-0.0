#include "IndexBuffer.h"
#include "Engine.h"
#include "GPUException.h"
#include <exception>
#include <Services.h>

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
	createGPUResource();
}

IndexBuffer::IndexBuffer(ISet* set,Buffer::Type t){
	_type = t;
	_buffer = set->getData();
	_changed = true;
	createGPUResource();
}

IndexBuffer::IndexBuffer(RAMBufferPtr buffer,Buffer::Type t){
	_type = t;
	_buffer = buffer;
	_changed = true;
	createGPUResource();
}

IndexBuffer::IndexBuffer(unsigned int size,Buffer::Type t){
	_type = t;
	_buffer = RAMBufferPtr(new RAMBuffer(size));
	_changed = true;
	createGPUResource();
}

IndexBuffer::IndexBuffer(const IndexBuffer& val):Buffer(val){
	_type = val._type;
}

IndexBuffer::~IndexBuffer(){
	//Infrastructure::Engine::Instance->GraphicsDevice->deleteBuffer(this);

	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::DEL;
	ins.args.push(Renderer::Arg(Renderer::GPU_ISA::INDEX_BUFFER));
	ins.args.push(Renderer::Arg(_handle.get()));

	Services::getGPU_VM()->execute(ins);
}

bool IndexBuffer::append(ISet* set){
	return _buffer->append(set->getData().get());
}

bool IndexBuffer::createGPUResource(){
	/*bool res = Engine::Instance->GraphicsDevice->createIndexBuffer(this);

	if(res)
		return res;
	else
		throw GPUException("Cannot create Index Buffer");*/

	Break::Renderer::GPUIns ins;
	ins.instruction = Break::Renderer::GPU_ISA::GEN;
	ins.args.push(Break::Renderer::Arg(Renderer::GPU_ISA::INDEX_BUFFER));
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

bool IndexBuffer::updateBuffer(unsigned int offset, unsigned int size){
	//return Engine::Instance->GraphicsDevice->updateIndexBuffer(this,offset,size);
	if(_type == Type::STATIC)
		throw GPUException("Cannot Map Index Buffer: Buffer type is not dynamic");

	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::MAP;
	ins.args.push(Renderer::Arg(Renderer::GPU_ISA::INDEX_BUFFER));
	ins.args.push(Renderer::Arg(_handle.get()));
	ins.args.push(Renderer::Arg(_buffer->getSize()));
	ins.args.push(Renderer::Arg(_buffer->getData()));

	Services::getGPU_VM()->execute(ins);
	return true;
}

void IndexBuffer::use(){
	//Engine::Instance->GraphicsDevice->useIndexBuffer(this);
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::BIND;
	ins.args.push(Renderer::Arg(Renderer::GPU_ISA::INDEX_BUFFER));
	ins.args.push(Renderer::Arg(_handle.get()));

	Services::getGPU_VM()->execute(ins);
}