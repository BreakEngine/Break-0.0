//#define LIBRARY_BUILD
#ifndef LIBRARY_BUILD
#include "Infrastructure.h"
#include "AudioTest.h"
#include "TestApplication.h"
#include <string>
#include "inc/Services.h"
#include "GlobalDefinitions.h"

using namespace std;
using namespace Break::Infrastructure;
using namespace glm;

int main(){	
	Engine::Instance->setup(make_shared<TestApp>(),API::DIRECTX);
	Engine::Instance->join(true);
	Engine::Instance->start();
	
	return 0;
}

#endif