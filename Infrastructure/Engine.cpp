#include "Engine.h"
#include <exception>
#include <iostream>
#include "../Renderer/GLManager.h"
#include "../Renderer/DXManager.h"
#include "Time.h"
using namespace std;
using namespace Break::Infrastructure;
using namespace Break::Renderer;
EnginePtr Engine::_instance = nullptr;
Property<EnginePtr,Engine,Permission::READ> Engine::Instance((*Engine::_instance.get()),&Engine::get,&Engine::set);
Engine::Engine():GraphicsDevice(*this,&Engine::getGraphicsDevice,NULL){
	_mainThread = NULL;
	_joinable = false;
	_cleaningUp = false;
	_renderer = nullptr;
	_graphicsManager = nullptr;
	_application = nullptr;
}
Engine::~Engine(){
	_cleaningUp = true;
	if(_mainThread && !_joinable)
		_mainThread->detach();
	if(_renderer)
		_renderer = nullptr;
	if(_graphicsManager)
		_graphicsManager= nullptr;
	if(_application)
		_application = nullptr;
	if(_inputDevices.size()>0){
		for(auto& device : _inputDevices){
			device = nullptr;
		}
		_inputDevices.clear();
	}
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
void Engine::setup(ApplicationPtr app,API api,IRendererPtr renderer){
	_api = api;
	_renderer = renderer;
	_application = app;
	if(_api == API::OPENGL){
		_graphicsManager = IGXManagerPtr(new GLManager());
	}else if(_api == API::DIRECTX){
		_graphicsManager = IGXManagerPtr(new DXManager());
	}else{
		throw exception("API parameter is not initialized");
	}
}

IGXManagerPtr Engine::getGraphicsDevice(){
	return _graphicsManager;
}

bool Engine::init(){
	try{
		//init graphics device manager
		_graphicsManager->init(_application);
		_graphicsManager->start();
		return true;
	}catch(exception e){
		cerr<<e.what()<<endl;
		return false;
	}
}

void Engine::start(){
	//for init application
	if(_application){
		_application->init();
		_application->loadResources();
		_application->setupScene();
	}

	if(_graphicsManager!=nullptr)
		_mainThread = new thread(&Engine::init,this);
	if(_mainThread && _joinable)
		_mainThread->join();

}
void Engine::join(bool val){
	_joinable = val;
}

void Engine::input(){
	_renderer->input();
	for(auto device : _inputDevices)
		device->update();
}

void Engine::update(TimeStep time){
	_renderer->update(time);
}

void Engine::render(){
	_renderer->render();
}

void Engine::gameloop(){
	if(_cleaningUp)
		return;

	//calculating delta
	double current = Time::getTime();
	if(Time::_lastTime == 0)
		Time::_lastTime = current;
	double delta = current - Time::_lastTime;
	Time::_lastTime = current;
	Time::_totalElapsedTime += delta;
	//increase the counter by the delta time
	Time::_counter += delta;
	Time::_secondTick += delta;
	//bool to indicate whether to render or not
	bool needRender = false;
	//check if a second passed
	if (Time::_secondTick >= 1){
		//reset second tick
		Time::_secondTick = 0;
		//setting the FPS
		Time::FPS = Time::_frameCounter;
		//reset frame counter
		Time::_frameCounter = 0;
	}
	if (Time::_type == Time::Type::LIMITED){
		//check if counter reached the frame limit in milliseconds
		if (Time::_counter > 1.0/Time::_frameLimit ){
			//set counter to 0 and 
			Time::_counter = 0;
			needRender = true;
		}
	}
	else if (Time::_type == Time::Type::UNLIMITED){
		//doesn't matter we always render as much as possible
		needRender = true;
	}
	//calling the processing functions every loop
	input();
	update(TimeStep(delta, Time::_totalElapsedTime));
	//if need render then render the scene
	if (needRender)
	{
		//increase frame count by one
		Time::_frameCounter++;
		render();
	}
}