#include "VertexDeclaration.h"

using namespace Break::GXWrapper;
using namespace Break;

VertexDeclaration::VertexDeclaration(){
	_size = 0;
}

VertexDeclaration::VertexDeclaration(std::vector<VertexElement>& e){
	_elements = e;
	calcSize();
}

VertexDeclaration::VertexDeclaration(VertexElement* e, uint count){
	for(int i=0;i<count;i++)
		_elements.push_back(e[i]);
	calcSize();
}

VertexDeclaration::VertexDeclaration(const VertexDeclaration& val){
	_elements = val._elements;
	_size = val._size;
}

uint VertexDeclaration::calcSize(){
	_size = 0;
	for(auto element : _elements){
		_size += element.size;
	}
	return _size;
}

void VertexDeclaration::append(VertexElement& v){
	if(v.offset == 0)
		v.offset = _size;
	_elements.push_back(v);
	_size += v.size;
}

uint VertexDeclaration::getSize(){
	return _size;
}

VertexDeclaration::~VertexDeclaration(){
	_elements.clear();
}