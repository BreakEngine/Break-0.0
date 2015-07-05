#pragma once

#include "ISet.h"
#include "GeometryHandle.h"
#include <memory>

namespace Break{
	namespace GXWrapper{
		class Geometry{
		private:
			MemoryLayout _declaration;
			GeometryHandle _handle;
		public:

			Geometry();
			Geometry(ISet* vertices, ISet* indices);

			Geometry(const Geometry& val);

			~Geometry();

			template<class T>
			T* getVertices(){
				T* head = reinterpret_cast<T*>(_handle.vertices->getData(_handle.verticesOffset));
				return head;
			}

			unsigned int* getIndices();

			unsigned int getVerticesCount();

			unsigned int getIndicesCount();
		};
		typedef std::shared_ptr<Geometry> GeometryPtr;
	}
}