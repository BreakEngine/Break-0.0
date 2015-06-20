#include "RAMBuffer.h"
#include "MemoryException.h"
#include <cstring>
using namespace Break::Infrastructure;
using namespace std;

RAMBuffer::RAMBuffer(unsigned int size){
	_fillStatus = 0;
	_size = size;
	_data = new byte[_size];
}

RAMBuffer::RAMBuffer(){
	_size = 0;
	_fillStatus = 0;
	_data = NULL;
}

RAMBuffer::RAMBuffer(void* ptr,unsigned int size, bool deep){
	if(!deep){
		_data = (byte*)ptr;
		_size = size;
		_fillStatus = size;
	}else{
		_fillStatus = size;
		_size = size;
		_data = new byte[_size];
		memcpy(_data,ptr,_size);
	}
}

RAMBuffer::RAMBuffer(const RAMBuffer& val){
	_size = val._size;
	_data = val._data;
	_fillStatus = val._fillStatus;
}

RAMBuffer::~RAMBuffer(){
	clear();
}

void RAMBuffer::clear(){
	if(_data)
	{
		delete[] _data;
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

bool RAMBuffer::append(RAMBufferPtr buffer){
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

RAMBufferPtr RAMBuffer::clone(){
	auto ret = make_shared<RAMBuffer>(_size);
	ret->append(_data,_size);
	return ret;
}