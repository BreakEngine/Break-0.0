#define LIBRARY_BUILD
#ifndef LIBRARY_BUILD
#include "Infrastructure.h"
#include "AudioTest.h"
#include "TestApplication.h"
using namespace std;
using namespace Break::Infrastructure;
using namespace glm;

int main(){	
	Engine::Instance->setup(make_shared<TestApp>(),API::DIRECTX);
	Engine::Instance->join(true);
	Engine::Instance->start();
	
	//note: jjiji
	//TODO: this needs cleaning up
	// FEATURE: Need to add support for XYZ
	//system("pause");
	return 0;
}

#endif