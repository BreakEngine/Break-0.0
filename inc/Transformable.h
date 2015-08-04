#pragma once
#include "Transform.h"

namespace Break
{
	namespace Graphics
	{
		class Transformable
		{
		public:
			Transform transform;

			Transformable(){}
			virtual ~Transformable(){}

			Transformable(const Transformable& val)
			{
				transform = val.transform;
			}
		};
	}
}