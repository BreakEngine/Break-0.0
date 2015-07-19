#pragma  once

#include "IVertex.h"
#include "MemoryLayout.h"

using namespace Break::GXWrapper;
using namespace glm;

class tv:public IVertex{
public:
	glm::vec4 _a;
	glm::vec4 _b;
	tv(vec4 a,vec4 b){
		_a = a;
		_b = b;
	}
	static MemoryLayout getDeclaration() {
		MemoryLayout ret;
		ret.append(MemoryElement(MemoryElement::VEC4,"POSITION"));
		ret.append(MemoryElement(MemoryElement::VEC4,"COLOR"));
		return ret;
	}

};