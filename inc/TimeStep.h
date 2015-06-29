#pragma once
namespace Break{
	namespace Infrastructure{
		class TimeStep{
		public:
			double delta, elapsedTime;
			TimeStep(double d=0,double e=0);

		};
	}
}