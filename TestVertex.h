#ifndef LIBRARY_BUILD
#pragma  once

#include "IVertex.h"
#include "MemoryLayout.h"

using namespace Break::GXWrapper;
using namespace glm;

class tv:public IVertex{
public:
	glm::vec4 _a;
	glm::vec4 _b;
	glm::vec2 _c;
	tv(vec4 a,vec4 b,vec2 t){
		_a = a;
		_b = b;
		_c = t;
	}
	static MemoryLayout getDeclaration() {
		MemoryLayout ret;
		ret.append(MemoryElement(MemoryElement::VEC4,"POSITION"));
		ret.append(MemoryElement(MemoryElement::VEC4,"COLOR"));
		ret.append(MemoryElement(MemoryElement::VEC2,"TEXCOORD"));
		return ret;
	}

};
#endif