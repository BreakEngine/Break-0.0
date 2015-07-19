#include "Infrastructure.h"
#include "TestApplication.h"


using namespace std;
using namespace Break::Infrastructure;
using namespace Break::GXWrapper;
using namespace glm;

int main(){	
	Engine::Instance->setup(make_shared<TestApp>(),API::DIRECTX);
	Engine::Instance->join(true);
	Engine::Instance->start();
	
	//system("pause");
	return 0;
}
