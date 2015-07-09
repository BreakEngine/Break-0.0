#pragma once

#include "ISet.h"
#include "GeometryHandle.h"
#include "GPUResource.h"
#include "IDrawable.h"
#include "Engine.h"
#include <memory>


namespace Break{
	namespace GXWrapper{

		class Geometry  :  public IDrawable , Infrastructure::GPUResource
		{
		private:
			MemoryLayout _declaration;
			GeometryHandle _handle;
		public:

			Geometry();
			Geometry(ISet* vertices, ISet* indices);

			Geometry(const Geometry& val);

			~Geometry();

			 bool createGPUResource();
			 void use();

			template<class T>
			T* getVertices()
			{
				T* head = reinterpret_cast<T*>(_handle.vertices->getData(_handle.verticesOffset));
				return head;
			}

			unsigned int* getIndices();

			unsigned int getVerticesCount();

			unsigned int getIndicesCount();

			void setInstance_Count(int _count);

			void Draw(IDrawable::Type _primative , IDrawable::Mode _mode);

		};
		typedef std::shared_ptr<Geometry> GeometryPtr;
	}
}