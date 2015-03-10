#include "DXManager.h"
using namespace Break::Renderer;
using namespace Break::Infrastructure;

DXManager::DXManager(){

}
DXManager::~DXManager(){

}

bool DXManager::init(ApplicationPtr app){
	//here comes the application pointer
	//you should take the IDisplay pointer and swap it with a similar Display<HWND> one with the same width, height, title
	return true;

}

void DXManager::start(){
	return;
}

void DXManager::clearBuffer(){

}
void DXManager::swapBuffer(){

}
void DXManager::setCursorPostion(glm::uvec2 val){

}