#pragma  once

#include "IVertex.h"
#include "MemoryLayout.h"

using namespace Break::GXWrapper;
using namespace glm;

class tv:public IVertex{
public:
	glm::vec3 _a;
	glm::vec4 _b;
	tv(float a){
		_a = vec3(a);
		_b = vec4(a);
	}
	static MemoryLayout getDeclaration() {
		MemoryLayout ret;
		ret.append(MemoryElement(MemoryElement::VEC3,"POSITION"));
		ret.append(MemoryElement(MemoryElement::VEC4,"COLOR"));
		return ret;
	}

};