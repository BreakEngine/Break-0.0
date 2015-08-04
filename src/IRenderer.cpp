#include"IRenderer.h"
#include"Engine.h"
using namespace Break::Infrastructure;
using namespace Break::Renderer;

IRenderer::IRenderer(){
}

IRenderer::~IRenderer(){
}

void IRenderer::input(){
	Engine::Instance->Application->input();
}

void IRenderer::update(TimeStep time){
	Engine::Instance->Application->update(time);
}

void IRenderer::render(){
	Engine::Instance->GraphicsDevice->clearBuffer();
	Engine::Instance->Application->render();
	Engine::Instance->GraphicsDevice->swapBuffer();
}