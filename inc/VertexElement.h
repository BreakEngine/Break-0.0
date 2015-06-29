#pragma once

#include "GlobalDefinitions.h"

namespace Break{
	namespace GXWrapper{
		class VertexElement{
		public:
			//type of the element
			enum Type{
				VEC2=0, VEC3=1, VEC4=2, FLOAT=3, INT=4, NONE=5
			};

			//type of the vertex element
			Type type;
			//element start offset in bytes
			uint offset;
			//element size in bytes
			uint size;
			//element component count
			uint components;

			VertexElement(uint _offset, uint _size, uint _components, Type _type = NONE){
				offset = _offset;
				size = _size;
				components = _components;
				type = _type;
			}

			VertexElement(Type _type){
				type = _type;
				offset = 0;
				switch (type)
				{
				case Break::GXWrapper::VertexElement::VEC2:
					size = sizeof(glm::vec2);
					components = 2;
					break;
				case Break::GXWrapper::VertexElement::VEC3:
					size = sizeof(glm::vec3);
					components = 3;
					break;
				case Break::GXWrapper::VertexElement::VEC4:
					size = sizeof(glm::vec4);
					components = 4;
					break;
				case Break::GXWrapper::VertexElement::FLOAT:
					size = sizeof(float);
					components = 1;
					break;
				case Break::GXWrapper::VertexElement::INT:
					size = sizeof(int);
					components = 1;
					break;
				case Break::GXWrapper::VertexElement::NONE:
					size = 0;
					components = 0;
					break;
				default:
					break;
				}
			}

			//copy constructor
			VertexElement(const VertexElement& val){
				offset = val.offset;
				size = val.size;
				components = val.components;
				type = val.type;
			}

			//default destructor
			~VertexElement(){

			}
		};
	}
}