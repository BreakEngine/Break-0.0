#ifdef _WIN32
#include "DXMouse.h"
#include<windows.h>
using namespace Break::Input;
using namespace std;

void DXMouse::mouseButton(int button, int state){
	if(state == 0)
		_data.insert(make_pair((Buttons)button,ButtonState::State_Down));
	else if(state == 1)
		_data[(Buttons)button] = ButtonState::State_Up;
	else
		_data.insert(make_pair((Buttons)button,ButtonState::State_None));
}

void DXMouse::update(){
	_data.clear();
}
void DXMouse::mouseMove(int x, int y){
	_position.x = x;
	_position.y = y;
}
#endif