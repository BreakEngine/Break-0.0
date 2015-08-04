//#include <vld.h>
#include "Infrastructure.h"
#include "TestApplication.h"

using namespace std;
using namespace Break::Infrastructure;
using namespace Break::GXWrapper;
using namespace glm;

int main(){	
	Engine::Instance->setup(make_shared<TestApp>(),API::OPENGL);
	Engine::Instance->join(true);
	Engine::Instance->start();
	
	//note: jjiji
	//TODO: this needs cleaning up
	// FEATURE: Need to add support for XYZ
	//system("pause");
	return 0;
}
