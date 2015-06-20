#include"Application.h"
#include"Engine.h"
using namespace Break::Infrastructure;

Application::Application(){
	_display = nullptr;
}

Application::~Application(){
	cleanUp();
	_display = nullptr;
}

IDisplayPtr Application::getDisplay(){
	return _display;
}

void Application::init(){

}
void Application::loadResources(){

}
void Application::setupScene(){

}

void Application::cleanUp(){

}

void Application::input(){

}
void Application::update(TimeStep time){

}
void Application::render(){

}

void Application::shutdown(){
	Engine::Instance->shutdown();
}