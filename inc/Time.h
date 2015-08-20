#pragma once
#include "Engine.h"
namespace Break{
	namespace Infrastructure{
		class TimeStep;
		///Time class to manage the time querys from the OS
		class Time{
			friend class Engine;
		public:
			///types of the time FPS class
			enum Type { UNLIMITED, LIMITED };
		private:
			///get time from os
			static double _freq;
			///check if timer is initialized
			static bool _init;
			///determines the number of frames per second
			static unsigned int _frameLimit;
			///register the last time
			static double _lastTime;
			///count time between frames
			static double _counter;
			///frame counter of frames per second
			static unsigned int _frameCounter;
			///tmp var to store time and reset every second
			static double _secondTick;
			///total elapsed time
			static double _totalElapsedTime;
			///last timeStep
			static TimeStep _previousStep;
			
			///the FPS
			static unsigned int FPS;
			///type of FPS
			static Type _type;
		public:
			static TimeStep getTimeStep();
			static double getTime();
			static void setFrameLimit(unsigned int );
			static unsigned int getFrameLimit();
			static Type getType();
			static void setType(Type);
			static unsigned int getFPS();

		};
	}
}