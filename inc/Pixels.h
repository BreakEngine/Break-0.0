#pragma once
#include <glm/detail/type_vec4.hpp>

namespace Break{
	namespace GXWrapper{

		/**
		 * \brief represents a pixel object (BGRA)
		 */
		struct Pixel{
			///pixel data
			unsigned char B,G,R,A;

			///defualt constructor
			Pixel()
			{
				R = 0;
				G = 0;
				B = 0;
				A = 0;
			}

			///vec4 init constructor
			Pixel(glm::vec4 val)
			{
				R = (unsigned char)(val.x*255.0f)%255;
				G = (unsigned char)(val.y*255.0f)%255;
				B = (unsigned char)(val.z*255.0f)%255;
				A = (unsigned char)(val.w*255.0f)%255;
			}

			///vec4 convert operator
			operator glm::vec4()
			{
				return vec4();
			}

			///vec4 convert function
			glm::vec4 vec4()
			{
				return glm::vec4(R/255.0f,G/255.0f,B/255.0f,A/255.0f);
			}

			///byte init constructor
			Pixel(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A):R(_R), G(_G), B(_B), A(_A){}
		};

		typedef Pixel Color;
	}
}