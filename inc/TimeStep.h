#pragma once
#include "GlobalDefinitions.h"
namespace Break{
	namespace Infrastructure{
		class BREAK_API_EX TimeStep{
		public:
			double delta, elapsedTime;
			TimeStep(double d=0,double e=0);

		};
	}
}