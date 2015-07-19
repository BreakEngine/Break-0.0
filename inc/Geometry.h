#pragma once

#include "ISet.h"
#include "GeometryData.h"
#include <memory>

namespace Break{
	namespace GXWrapper{
		class Geometry: public IDrawable, Infrastructure::GPUResource{
			friend class Renderer::GLManager;
			friend class Renderer::DXManager;
		private:
			MemoryLayout _declaration;
			GeometryData _geometryData;
		protected:
			virtual bool createGPUResource()override;
		public:
			Geometry(ISet* vertices, ISet* indices,Primitive::Type type);

			Geometry(const Geometry& val);

			~Geometry();

			template<class T>
			T* getVertices(){
				T* head = reinterpret_cast<T*>(_geometryData.vertices->getData(_geometryData.verticesOffset));
				return head;
			}

			unsigned int* getIndices();

			unsigned int getVerticesCount();

			unsigned int getIndicesCount();

			MemoryLayout getMemoryLayout();

			GeometryData getGeometryData();

			virtual void draw(Primitive::Mode mode)override;
		};
		typedef std::shared_ptr<Geometry> GeometryPtr;
	}
}