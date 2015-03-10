#include"Application.h"
using namespace Break::Infrastructure;

Application::Application(){
	_display = nullptr;
}

Application::~Application(){
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