#include "RAMBuffer.h"
#include "MemoryException.h"
#include <cstring>
using namespace Break::Infrastructure;
using namespace Break;
using namespace std;

RAMBuffer::RAMBuffer(unsigned int size){
	_fillStatus = 0;
	_size = size;
	_data = new byte[_size];
	_shouldDelete = true;
}

RAMBuffer::RAMBuffer(){
	_size = 0;
	_fillStatus = 0;
	_data = NULL;
	_shouldDelete = true;
}


RAMBuffer::RAMBuffer(const RAMBuffer& val){
	_size = val._size;
	_data = val._data;
	_fillStatus = val._fillStatus;
	_shouldDelete = false;
}

RAMBuffer::~RAMBuffer(){
	if(_data && _shouldDelete)
		delete[] _data;
}

void RAMBuffer::clear(){
	if(_data)
	{
		_fillStatus = 0;
		//_data = NULL;
	}
}

bool RAMBuffer::append(void* data,unsigned int size){
	if(_fillStatus + size <= _size){
		memcpy(_data+_fillStatus,data,size);
		_fillStatus += size;
		return true;
	}else{
		throw MemoryException("Memory out of bound");
	}
}

bool RAMBuffer::append(RAMBuffer* buffer){
	if(_fillStatus+buffer->_fillStatus<=_size){
		memcpy(_data+_fillStatus,buffer->_data,buffer->_fillStatus);
		_fillStatus += buffer->_fillStatus;
		return true;
	}else{
		throw MemoryException("Memory out of bound");
	}
}

bool RAMBuffer::map(void* data,unsigned int size,unsigned int start){
	if(start+size<=_size){
		memcpy(_data+start,data,size);
		return true;
	}else{
		throw MemoryException("Memory out of bound");
	}
}

void RAMBuffer::reallocate(unsigned int size){
	clear();
	_size = size;
	_fillStatus = 0;
	_data = new byte[_size];
}

byte* RAMBuffer::getData(unsigned int offset){
	if(offset<=_size)
		return (byte*)(_data+offset);
	else
		return NULL;
}

unsigned int RAMBuffer::getSize(){
	return _size;
}

unsigned int RAMBuffer::getUsedSize(){
	return _fillStatus;
}


void RAMBuffer::deleteBuffer()
{
	if(_data)
		delete[] _data;
}

RAMBufferPtr RAMBuffer::clone(){
	auto ret = make_shared<RAMBuffer>(_size);
	ret->append(_data,_size);
	return ret;
}

void RAMBuffer::copyHandle(void* ptr,u32 size)
{
		_data = (byte*)ptr;
		_size = size;
		_fillStatus = size;
		_shouldDelete = false;
}


void RAMBuffer::copyBuffer(void* ptr,u32 size)
{
		_fillStatus = size;
		_size = size;
		_data = new byte[_size];
		memcpy(_data,ptr,_size);
		_shouldDelete = true;
}

