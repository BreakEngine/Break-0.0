#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <memory>
#include "IDrawable.h"

namespace Break{
	namespace GXWrapper{
		/**
		 * \brief holds geometry data
		 * \author Moustapha Saad
		 */
		class GeometryData{
		public:
			///vertex buffer pointer
			std::shared_ptr<VertexBuffer> vertices;
			///index buffer pointer
			std::shared_ptr<IndexBuffer> indices;

			///vertices offset in the buffer
			unsigned int verticesOffset;
			///vertices count in buffer
			unsigned int verticesCount;

			///indices offset in buffer
			unsigned int indicesOffset;
			///indices count in buffer
			unsigned int indicesCount;

			///primitive type of the geometry
			Primitive::Type primitive;

			///indtance count in case of instancing
			unsigned int instanceCount;

			///default constructor
			GeometryData(){
				instanceCount = 1;
				vertices = nullptr;
				indices = nullptr;
				primitive = Primitive::TRIANGLES;
			}

			///default destructor
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

			///default destructor
			~GeometryData(){
				if(vertices)
					vertices = nullptr;
				if(indices)
					indices = nullptr;
			}
		};
	}
}