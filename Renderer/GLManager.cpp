#include "GLManager.h"
using namespace Break::Renderer;
using namespace Break::Infrastructure;

GLManager::GLManager(){

}
GLManager::~GLManager(){

}

bool GLManager::init(ApplicationPtr app){
	//here comes the application pointer
	//you should take the IDisplay pointer and swap it with a similar Display<HWND> one with the same width, height, title
	return true;
}

void GLManager::start(){
	return;
}

void GLManager::clearBuffer(){

}
void GLManager::swapBuffer(){

}
void GLManager::setCursorPostion(glm::uvec2 val){

}