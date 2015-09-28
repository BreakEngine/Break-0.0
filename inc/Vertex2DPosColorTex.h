#pragma once
#include "IVertex.h"
#include <glm/common.hpp>
#include "MemoryLayout.h"
#include "GlobalDefinitions.h"

namespace Break
{
	namespace Assets
	{
		class BREAK_API_EX Vertex2DPosColorTex: public GXWrapper::IVertex
		{
		public:
			glm::vec2 position;
			glm::vec4 color;
			glm::vec2 texCoord;

			Vertex2DPosColorTex()
			{
				
			}
			Vertex2DPosColorTex(glm::vec2 pos,glm::vec4 _color, glm::vec2 _tex):position(pos), color(_color),
			texCoord(_tex){}

			static GXWrapper::MemoryLayout getDescription()
			{
				GXWrapper::MemoryLayout res;
				res.append(GXWrapper::MemoryElement(GXWrapper::MemoryElement::VEC2,"POSITION"));
				res.append(GXWrapper::MemoryElement(GXWrapper::MemoryElement::VEC4,"COLOR"));
				res.append(GXWrapper::MemoryElement(GXWrapper::MemoryElement::VEC2,"TEXCOORD"));
				return res;
			}
		};
	}
}