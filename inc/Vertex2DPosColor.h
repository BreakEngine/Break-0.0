#pragma once
#include "IVertex.h"
#include <glm/common.hpp>
#include "MemoryLayout.h"

namespace Break
{
	namespace Assets
	{
		class Vertex2DPos: public GXWrapper::IVertex
		{
		public:
			glm::vec2 position;
			glm::vec4 color;

			explicit Vertex2DPos(glm::vec2 pos):position(pos){}

			static GXWrapper::MemoryLayout getDescription()
			{
				GXWrapper::MemoryLayout res;
				res.append(GXWrapper::MemoryElement(GXWrapper::MemoryElement::VEC2,"POSITION"));
				res.append(GXWrapper::MemoryElement(GXWrapper::MemoryElement::VEC4,"COLOR"));
				return res;
			}
		};
	}
}