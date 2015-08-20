#include"Application.h"
#include"Engine.h"
using namespace Break::Infrastructure;

Application::Application(){
	display =nullptr;
	scene = NULL;
}

Application::~Application(){
	cleanUp();
	display = nullptr;
	if(scene)
		delete scene;
}

IDisplayPtr Application::getDisplay(){
	return display;
}

void Application::init(){
	scene = new Graphics::Scene();
	spriteBatch = scene->spriteBatch;
}
void Application::loadResources(){

}
void Application::setupScene(){

}

void Application::cleanUp(){

}

void Application::input(){
	scene->input();
}
void Application::update(TimeStep time){
	scene->update(time);
}
void Application::render(){
	scene->draw();
}

void Application::shutdown(){
	Engine::Instance->shutdown();
}