#include "VertexDeclaration.h"
using namespace Break::GXWrapper;

VertexDeclaration::VertexDeclaration(const VertexDeclaration& val){
	_stride = val._stride;
	_elements = val._elements;
}

VertexDeclaration::VertexDeclaration(int stride, VertexElement* elements,int elementsC){
	_stride = stride;
	_elements = std::vector<VertexElement>(elements,elements+elementsC);
}

VertexDeclaration::~VertexDeclaration(){
	_elements.clear();
}