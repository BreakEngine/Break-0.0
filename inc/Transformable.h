#pragma once
#include "Transform.h"
#include "GlobalDefinitions.h"

namespace Break
{
	namespace Graphics
	{
		///represents a transformable object
		class BREAK_API_EX Transformable
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