#pragma once

#include "GlobalDefinitions.h"
#include <string>

namespace Break{
	namespace GXWrapper{
		class MemoryElement{
		public:
			//type of the element
			enum Type{
				VEC2=0, VEC3, VEC4, FLOAT, INT, BOOL, MAT3, MAT4, NONE
			};

			//type of the vertex element
			Type type;
			//element start offset in bytes
			uint offset;
			//element size in bytes
			uint size;
			//element component count
			uint components;
			//
			std::string semantic;

			MemoryElement(uint _offset, uint _size, uint _components, Type _type = NONE,std::string _semantic=""){
				offset = _offset;
				size = _size;
				components = _components;
				type = _type;
				semantic = _semantic;
			}

			MemoryElement(Type _type, std::string _semantic){
				type = _type;
				offset = 0;
				semantic = _semantic;
				switch (type)
				{
				case Break::GXWrapper::MemoryElement::VEC2:
					size = sizeof(glm::vec2);
					components = 2;
					break;
				case Break::GXWrapper::MemoryElement::VEC3:
					size = sizeof(glm::vec3);
					components = 3;
					break;
				case Break::GXWrapper::MemoryElement::VEC4:
					size = sizeof(glm::vec4);
					components = 4;
					break;
				case Break::GXWrapper::MemoryElement::FLOAT:
					size = sizeof(float);
					components = 1;
					break;
				case Break::GXWrapper::MemoryElement::INT:
					size = sizeof(int);
					components = 1;
					break;
				case Break::GXWrapper::MemoryElement::BOOL:
					size = sizeof(bool);
					components = 1;
					break;
				case Break::GXWrapper::MemoryElement::MAT3:
					size = sizeof(float)*9;
					components = 1;
					break;
				case Break::GXWrapper::MemoryElement::MAT4:
					size = sizeof(float)*16;
					components = 1;
					break;
				case Break::GXWrapper::MemoryElement::NONE:
					size = 0;
					components = 0;
					break;
				default:
					break;
				}
			}

			bool equals(const MemoryElement& val)
			{
				bool res = false;

				if(	offset == val.offset &&
					size == val.size	 &&
					components == val.components &&
					type == val.type &&
					semantic == val.semantic
				  )
				{
					res = true;
				}

				return res;

			}
			//copy constructor
			MemoryElement(const MemoryElement& val){
				offset = val.offset;
				size = val.size;
				components = val.components;
				type = val.type;
				semantic = val.semantic;
			}

			//default destructor
			~MemoryElement(){

			}
		};
	}
}