#pragma once
#include <memory>
#include "VertexDeclaration.h"
namespace Break{
	namespace GXWrapper{
		//this class shall encapsulate the vertices's data
		class IVertex{
		public:
			static VertexDeclaration getVertexDeclaration();
			IVertex();
			virtual ~IVertex();
		};
		typedef std::shared_ptr<IVertex> IVertexPtr;
	}
}