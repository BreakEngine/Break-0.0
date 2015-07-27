#pragma once

namespace Break{
	namespace GXWrapper{
		struct Pixel{
			unsigned char R,G,B,A;

			Pixel()
			{
				R = 0;
				G = 0;
				B = 0;
				A = 0;
			}
			Pixel(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A):R(_R), G(_G), B(_B), A(_A){}
		};

		typedef Pixel Color;
	}
}