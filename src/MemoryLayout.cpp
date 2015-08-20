#include "MemoryLayout.h"

using namespace Break::GXWrapper;
using namespace Break;

MemoryLayout::MemoryLayout(){
	_size = 0;
}

MemoryLayout::MemoryLayout(std::vector<MemoryElement>& e){
	elements = e;
	calcSize();
}

MemoryLayout::MemoryLayout(MemoryElement* e, uint count){
	for(int i=0;i<count;i++)
		elements.push_back(e[i]);
	calcSize();
}

MemoryLayout::MemoryLayout(const MemoryLayout& val){
	elements = val.elements;
	_size = val._size;
}

uint MemoryLayout::calcSize(){
	_size = 0;
	for(auto element : elements){
		_size += element.size;
	}
	return _size;
}

void MemoryLayout::append(MemoryElement v){
	if(v.offset == 0)
		v.offset = _size;
	elements.push_back(v);
	_size += v.size;
}

uint MemoryLayout::getSize(){
	return _size;
}

MemoryLayout::~MemoryLayout(){
	elements.clear();
}

uint MemoryLayout::getElementCount(){
	return elements.size();
}

bool MemoryLayout::equals(const MemoryLayout& val)
{
	if(_size != val._size)
		return false;

	if(val.elements.size() != elements.size())
		return false;

	for(int i=0;i<elements.size();i++)
		if(!elements[i].equals(val.elements[i])){
			return false;
		}
	return true;
}