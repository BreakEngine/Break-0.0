#include"IGXManager.h"
using namespace Break::Infrastructure;

IGXManager::IGXManager(){

}

IGXManager::~IGXManager(){

}

bool IGXManager::init(ApplicationPtr app){
	return true;
}

void IGXManager::start(){
	return;
}

void IGXManager::clearBuffer(){

}

void IGXManager::swapBuffer(){

}

void IGXManager::setCursorPostion(glm::uvec2 val){

}
/*
bool IGXManager::createBuffer(GXWrapper::VertexBuffer& buffer){
	return false;
}

bool IGXManager::createBuffer(GXWrapper::IndexBuffer& buffer){
	return false;
}*/