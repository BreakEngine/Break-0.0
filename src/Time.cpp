#include "Time.h"
#include <exception>
#if defined(WIN32) ||defined(_WIN32) || defined(__WIN32__)|| defined(_WIN64) || defined(WIN64)
#define WINDOWS
#include <windows.h>
#elif defined(__linux__) || defined(__unix__)
#define OS_LINUX
#include <sys/time.h>
#include <bits/time.h>
#include <time.h>
static const long NANOSECONDS_PER_SECOND = 1000000000L;
#endif

using namespace Break::Infrastructure;
using namespace std;

double Time::_freq = 0;
bool Time::_init = false;
Time::Type Time::_type = Time::Type::LIMITED;
unsigned int Time::_frameLimit = 60;
double Time::_lastTime = 0;
double Time::_counter = 0;
double Time::_secondTick = 0;
unsigned int Time::_frameCounter = 0;
double Time::_totalElapsedTime = 0;
unsigned int Time::FPS = 0;
TimeStep Time::_previousStep = TimeStep(0,0);

TimeStep Time::getTimeStep()
{
	return _previousStep;
}

double Time::getTime(){
#ifdef WINDOWS
	LARGE_INTEGER li;
	if(!_init){
		if(!QueryPerformanceFrequency((&li)))
			throw exception("Can't initialize the frequency timer");
		_freq = double(li.QuadPart);
		_init = true;
	}

	if(!QueryPerformanceCounter((&li))){
		throw exception("QueryPerformanceCounter can't get the time");
	}
	return double(li.QuadPart)/_freq;
#endif
#ifdef OS_LINUX
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (double)(((long) ts.tv_sec * NANOSECONDS_PER_SECOND) + ts.tv_nsec)/((double)(NANOSECONDS_PER_SECOND));
#endif
}

void Time::setFrameLimit(unsigned int limit){
	if(limit>0)
		_frameLimit = limit;
}
unsigned int Time::getFrameLimit(){
	return _frameLimit;
}

void Time::setType(Type val){
	_type = val;
}

Time::Type Time::getType(){
	return _type;
}

unsigned int Time::getFPS(){
	return FPS;
}