#pragma once
#include "TimeStep.h"
#include "GlobalDefinitions.h"
namespace Break
{
	namespace GXWrapper
	{
		/**
		 * \brief insterface to update functions
		 * \author Moustapha Saad
		 */
		class BREAK_API_EX IUpdateable
		{
		public:
			virtual void input()=0;
			virtual void update(Infrastructure::TimeStep tick)=0;
		};
	}
}