#pragma once
#include "TimeStep.h"
namespace Break
{
	namespace GXWrapper
	{
		/**
		 * \brief insterface to update functions
		 * \author Moustapha Saad
		 */
		class IUpdateable
		{
		public:
			virtual void input()=0;
			virtual void update(Infrastructure::TimeStep tick)=0;
		};
	}
}