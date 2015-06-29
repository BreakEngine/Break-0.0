#include <iostream>
#include <string>
#include "Infrastructure.h"
#include "TestApplication.h"
#include "TestVertex.h"
#include <chrono>
#include <typeinfo>


using namespace std;
using namespace Break::Infrastructure;
using namespace Break::GXWrapper;
using namespace glm;
using namespace std::chrono;

int main(){	
	Engine::Instance->setup(make_shared<TestApp>(),API::DIRECTX);
	Engine::Instance->join(true);
	Engine::Instance->start();
	
	//system("pause");
	return 0;
}
