#define GLM_FORCE_RADIANS
#include "Engine.h"
#include <exception>
#include <iostream>
#include "GLManager.h"
#include "DXManager.h"
#include "Time.h"
#include "GLKeyboard.h"
#include "DXKeyboard.h"
#include "GLMouse.h"
#include "DXMouse.h"
#include "AssetManager.h"
#include "Services.h"
#include <glm/gtc/matrix_transform.hpp>
#include <SDL_mixer.h>
using namespace std;
using namespace Break::Infrastructure;
using namespace Break::Renderer;
EnginePtr Engine::_instance = nullptr;

#pragma comment(lib,"SDL2_mixer.lib")
#pragma comment(lib,"SDL2.lib")

Property<EnginePtr,Engine,Permission::READ> Engine::Instance((*Engine::_instance.get()),&Engine::get,&Engine::set);

Engine::Engine():GraphicsDevice(*this,&Engine::getGraphicsDevice,NULL),
	Application(*this,&Engine::getApplication,NULL)
{
	_mainThread = NULL;
	_joinable = false;
	_cleaningUp = false;
	_renderer = nullptr;
	_graphicsManager = nullptr;
	_application = nullptr;
	_gpuVM = nullptr;
	_shutdown = false;
	_initFinished = false;
}

Engine::~Engine(){
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
	_gpuVM = new GPU_VM();

	if(_api == API::OPENGL){
		_graphicsManager = IGXManagerPtr(new GLManager());
		_inputDevices.push_back(IKeyboardPtr(new Input::GLKeyboard()));
		_inputDevices.push_back(IMousePtr(new Input::GLMouse()));
	}else if(_api == API::DIRECTX){
		#ifdef _WIN32
		_graphicsManager = IGXManagerPtr(new DXManager());
		_inputDevices.push_back(IKeyboardPtr(new Input::DXKeyboard()));
		_inputDevices.push_back(IMousePtr(new Input::DXMouse()));
		#endif
	}else{
		throw runtime_error("API parameter is not initialized");
	}
	Services::registerEngine(this);
	Services::registerGraphics(_graphicsManager.get());
	Services::registerVM(_gpuVM);
}

IGXManagerPtr Engine::getGraphicsDevice(){
	return _graphicsManager;
}
ApplicationPtr Engine::getApplication(){
	return _application;
}

void Engine::initAudio()
{
	Mix_Init(0);
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY*2,MIX_DEFAULT_FORMAT,2,2048)<0)
	{
		std::cerr<<"Cannot initialize audio"<<std::endl;
	}
}
bool Engine::init(){
	try{
		//init graphics device manager
		initAudio();
		_initFinished = _graphicsManager->init(_application);
		Assets::AssetManager::addDefaultAssets();
		if(_application){
			_2DOrthographic = glm::ortho(0.0f,(float)_application->getDisplay()->getWidth(),(float)_application->getDisplay()->getHeight(),0.0f,-10.0f,10.0f);
			_application->init();
			_application->loadResources();
			_application->setupScene();
		}
		_graphicsManager->start();

		cleanUp();

		return true;
	}catch(exception e){
		cerr<<e.what()<<endl;
		return false;
	}
}

void Engine::cleanUp(){
	_cleaningUp = true;
	if(_mainThread && !_joinable)
		_mainThread->detach();
	Assets::AssetManager::cleanUp();
	if(_renderer)
		_renderer = nullptr;
	if(_application)
		_application = nullptr;
	if(_graphicsManager)
		_graphicsManager= nullptr;
	if(_inputDevices.size()>0){
		for(auto& device : _inputDevices){
			device = nullptr;
		}
		_inputDevices.clear();
	}
	if(_gpuVM)
		delete _gpuVM;
	Mix_Quit();
}

IRenderer* Engine::getRenderer()
{
	return this->_renderer.get();
}

API Engine::getAPI()
{
	return _api;
}

glm::mat4 Engine::get2DOrthogonal()
{
	return _2DOrthographic;
}

void Engine::start(){
	if(_graphicsManager!=nullptr)
		_mainThread = new thread(&Engine::init,this);

	if(_mainThread && _joinable)
		_mainThread->join();

	//for init application
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
	Time::_previousStep.delta = delta;
	Time::_previousStep.elapsedTime = Time::_totalElapsedTime;
	update(Time::_previousStep);
	//if need render then render the scene
	if (needRender)
	{
		//increase frame count by one
		Time::_frameCounter++;

		render();
	}
	else
	{
		//this_thread::sleep_for(chrono::duration<int,milli>(1));
	}
}

void Engine::shutdown(){
	_shutdown = true;
}