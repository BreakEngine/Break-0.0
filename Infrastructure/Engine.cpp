#include "Engine.h"
#include <exception>
#include <iostream>
using namespace std;
using namespace Break::Infrastructure;
EnginePtr Engine::_instance = nullptr;
Property<EnginePtr,Engine,Permission::READ> Engine::Instance((*Engine::_instance.get()),&Engine::get,&Engine::set);
Engine::Engine(){
	_mainThread = NULL;
	_api = API::NONE;
	_joinable = false;
	_cleaningUp = false;
	_renderer = nullptr;
	_graphicsManager = nullptr;
}
Engine::~Engine(){
	_cleaningUp = true;
	if(_mainThread && !_joinable)
		_mainThread->detach();
	if(_renderer)
		_renderer = nullptr;
	if(_graphicsManager)
		_graphicsManager= nullptr;
	delete _mainThread;
}
EnginePtr Engine::get(){
	if(!Engine::_instance)
		Engine::_instance = EnginePtr(new Engine());
	return _instance;
}
void Engine::set(EnginePtr val){
	return;
}
void Engine::setup(API api,IRendererPtr renderer){
	_api = api;
	_renderer = renderer;
	if(_api == API::OPENGL){

	}else if(_api == API::DIRECTX){

	}else{
		throw exception("API parameter is not initialized");
	}
}

bool Engine::init(){
	return false;
}

void Engine::start(){

}
void Engine::join(bool val){
	_joinable = val;
}

void Engine::input(){

}

void Engine::update(){

}

void Engine::render(){

}

void Engine::gameloop(){

}