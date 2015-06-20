#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <memory>

namespace Break{
	namespace GXWrapper{
		class GeometryHandle{
		public:
			std::shared_ptr<VertexBuffer> vertices;
			std::shared_ptr<IndexBuffer> indices;

			unsigned int verticesOffset;
			unsigned int verticesCount;

			unsigned int indicesOffset;
			unsigned int indicesCount;

			GeometryHandle(){
				vertices = nullptr;
				indices = nullptr;
			}

			GeometryHandle(const GeometryHandle& val){
				vertices = val.vertices;
				indices = val.indices;

				verticesCount = val.verticesCount;
				verticesOffset = val.verticesOffset;

				indicesCount = val.indicesCount;
				indicesOffset = val.indicesOffset;
			}

			~GeometryHandle(){
				vertices = nullptr;
				indices = nullptr;
			}
		};
	}
}