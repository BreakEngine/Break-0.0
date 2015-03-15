#include "VertexElement.h"
using namespace Break::GXWrapper;

VertexElement::VertexElement(int offset, int size, int components){
	_offset = offset;
	_size = size;
	_components = components;
}

VertexElement::VertexElement(const VertexElement& val){
	_offset = val._offset;
	_size = val._size;
	_components = val._components;
}

VertexElement::~VertexElement(){

}