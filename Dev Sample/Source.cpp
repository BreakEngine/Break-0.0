#include <iostream>
#include "../Infrastructure/Engine.h"
using namespace std;
using namespace Break::Infrastructure;
int main(){
	EnginePtr engine = Engine::Instance;
	engine->setup(API::OPENGL);
	engine->start();
	int x = 0;
	cin>>x;
	return 0;
}
