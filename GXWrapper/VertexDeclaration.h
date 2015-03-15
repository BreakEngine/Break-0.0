#pragma once
#include "VertexElement.h"
#include <vector>
namespace Break{
	namespace GXWrapper{
		class VertexDeclaration{
		private:
			//storing elements of vertex
			std::vector<VertexElement> _elements;
			//storing stride the exact size of each vertex
			unsigned int _stride;

		public:

			VertexDeclaration(int stride, VertexElement* elements,int elementsC);
			//copy constructor
			VertexDeclaration(const VertexDeclaration& val);
			virtual ~VertexDeclaration();
		};
	}
}