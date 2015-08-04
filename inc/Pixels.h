#pragma once
#include <glm/detail/type_vec4.hpp>

namespace Break{
	namespace GXWrapper{
		struct Pixel{
			unsigned char B,G,R,A;

			Pixel()
			{
				R = 0;
				G = 0;
				B = 0;
				A = 0;
			}

			Pixel(glm::vec4 val)
			{
				R = (unsigned char)(val.x*255)%255;
				G = (unsigned char)(val.y*255)%255;
				B = (unsigned char)(val.z*255)%255;
				A = (unsigned char)(val.w*255)%255;
			}

			operator glm::vec4()
			{
				return vec4();
			}

			glm::vec4 vec4()
			{
				return glm::vec4(R/255,G/255,B/255,A/255);
			}
			Pixel(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A):R(_R), G(_G), B(_B), A(_A){}
		};

		typedef Pixel Color;
	}
}