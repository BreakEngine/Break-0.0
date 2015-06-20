#pragma once

#include "VertexElement.h"
#include <vector>

namespace Break{
	namespace GXWrapper{
		class VertexDeclaration{
		protected:
			//size of full data
			uint _size;
			//elements vector
			std::vector<VertexElement> _elements;

			uint calcSize();
		public:
			VertexDeclaration();
			VertexDeclaration(std::vector<VertexElement>& e);
			VertexDeclaration(VertexElement* e, uint count);
			VertexDeclaration(const VertexDeclaration& val);

			void append(VertexElement& v);

			uint getSize();

			~VertexDeclaration();

		};
	}
}