#include <iostream>
#include<string>
#include "../Infrastructure/Engine.h"
#include "TestApplication.h"
using namespace std;
using namespace Break::Infrastructure;
int main(){
	EnginePtr engine = Engine::Instance;
	engine->setup(ApplicationPtr(new TestApp()),API::DIRECTX);
	engine->start();
	int x = 0;
	cin>>x;
	return 0;
}
