#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <memory>
#include "IDrawable.h"

namespace Break{
	namespace GXWrapper{
		class GeometryData{
		public:
			std::shared_ptr<VertexBuffer> vertices;
			std::shared_ptr<IndexBuffer> indices;

			unsigned int verticesOffset;
			unsigned int verticesCount;

			unsigned int indicesOffset;
			unsigned int indicesCount;

			Primitive::Type primitive;

			unsigned int instanceCount;

			GeometryData(){
				instanceCount = 1;
				vertices = nullptr;
				indices = nullptr;
				primitive = Primitive::TRIANGLES;
			}

			GeometryData(const GeometryData& val){
				vertices = val.vertices;
				indices = val.indices;

				verticesCount = val.verticesCount;
				verticesOffset = val.verticesOffset;

				indicesCount = val.indicesCount;
				indicesOffset = val.indicesOffset;
				primitive = val.primitive;
				instanceCount = val.instanceCount;
			}

			~GeometryData(){
				if(vertices)
					vertices = nullptr;
				if(indices)
					indices = nullptr;
			}
		};
	}
}