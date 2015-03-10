#include "IMouse.h"
#include "Engine.h"
using namespace Break::Infrastructure;
using namespace std;

map<IMouse::Buttons,IMouse::ButtonState> IMouse::_data = map<IMouse::Buttons,IMouse::ButtonState>();
glm::uvec2 IMouse::_position = glm::uvec2();

IMouse::IMouse(){
	_data.clear();
}
IMouse::~IMouse(){
	_data.clear();
}
void IMouse::update(){

}
IMouse::ButtonState IMouse::getButton(IMouse::Buttons b){
	auto it = _data.find(b);
	if(it == _data.end())
		return IMouse::ButtonState::State_None;
	return it->second;
}
glm::uvec2 IMouse::getPosition(){
	return _position;
}
void IMouse::setPosition(glm::uvec2 val){
	Engine::Instance->GraphicsDevice->setCursorPostion(val);
}