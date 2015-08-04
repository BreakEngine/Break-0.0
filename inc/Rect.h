#pragma once

namespace Break
{
	namespace Graphics
	{
		struct Rect
		{
			float x,y,width,height;
			Rect(){x=0;y=0;width=0;height=0;}
			Rect(float _x,float _y, float _width, float _height)
			{
				x=_x;
				y=_y;
				width=_width;
				height = _height;
			}
		};
	}
}