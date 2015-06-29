#pragma  once

#include "IVertex.h"
#include "VertexDeclaration.h"

using namespace Break::GXWrapper;
using namespace glm;

class tv:public IVertex{
public:
	float _a;
	glm::vec2 _b;
	tv(float a){
		_a = a;
		_b = vec2(a);
	}
	static VertexDeclaration getDeclaration() {
		VertexDeclaration ret;
		ret.append(VertexElement(VertexElement::FLOAT));
		ret.append(VertexElement(VertexElement::VEC2));
		return ret;
	}

};