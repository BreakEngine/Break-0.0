#include "GLMouse.h"
#include <utility>
using namespace Break::Input;
using namespace std;

void GLMouse::mouseFunc(GLFWwindow* window, int button, int action, int mods){
	if(button == GLFW_MOUSE_BUTTON_LEFT){
		if(action == GLFW_PRESS)
			_data.insert(make_pair(Buttons::Left_Button,ButtonState::State_Down));
		else if(action == GLFW_RELEASE)
			_data.insert(make_pair(Buttons::Left_Button,ButtonState::State_Up));
	}else if(button == GLFW_MOUSE_BUTTON_RIGHT){
		if(action == GLFW_PRESS)
			_data.insert(make_pair(Buttons::Right_Button,ButtonState::State_Down));
		else if(action == GLFW_RELEASE)
			_data.insert(make_pair(Buttons::Right_Button,ButtonState::State_Up));
	}else if(button == GLFW_MOUSE_BUTTON_MIDDLE){
		if(action == GLFW_PRESS)
			_data.insert(make_pair(Buttons::Middle_Button,ButtonState::State_Down));
		else if(action == GLFW_RELEASE)
			_data.insert(make_pair(Buttons::Middle_Button,ButtonState::State_Up));
	}
		
}

void GLMouse::update(){
	_data.clear();
}

void GLMouse::mouseMotion(GLFWwindow* window,double x, double y){
	_position.x = x;
	_position.y = y;
}