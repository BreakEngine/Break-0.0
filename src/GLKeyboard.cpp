#include"GLKeyboard.h"
#include<GLFW/glfw3.h>
#include<utility>
using namespace std;
using namespace Break::Input;


void GLKeyboard::update(){
	IKeyboard::_data.clear();
}
void GLKeyboard::keyboardFunc(GLFWwindow* window, int key, int scancode, int action, int mods){
	switch (key)
	{
	case GLFW_KEY_A:
		_data.insert(make_pair(Keys::A, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_B:
		_data.insert(make_pair(Keys::B, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_C:
		_data.insert(make_pair(Keys::C, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_D:
		_data.insert(make_pair(Keys::D, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_E:
		_data.insert(make_pair(Keys::E, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_F:
		_data.insert(make_pair(Keys::F, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_G:
		_data.insert(make_pair(Keys::G, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_H:
		_data.insert(make_pair(Keys::H, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_I:
		_data.insert(make_pair(Keys::I, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_J:
		_data.insert(make_pair(Keys::J, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_K:
		_data.insert(make_pair(Keys::K, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_L:
		_data.insert(make_pair(Keys::L, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_M:
		_data.insert(make_pair(Keys::M, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_N:
		_data.insert(make_pair(Keys::N, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_O:
		_data.insert(make_pair(Keys::O, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_P:
		_data.insert(make_pair(Keys::P, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_Q:
		_data.insert(make_pair(Keys::Q, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_R:
		_data.insert(make_pair(Keys::R, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_S:
		_data.insert(make_pair(Keys::S, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_T:
		_data.insert(make_pair(Keys::T, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_U:
		_data.insert(make_pair(Keys::U, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_V:
		_data.insert(make_pair(Keys::V, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_W:
		_data.insert(make_pair(Keys::W, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_X:
		_data.insert(make_pair(Keys::X, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_Y:
		_data.insert(make_pair(Keys::Y, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_Z:
		_data.insert(make_pair(Keys::Z, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_0:
		_data.insert(make_pair(Keys::Num_0, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_1:
		_data.insert(make_pair(Keys::Num_1, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_2:
		_data.insert(make_pair(Keys::Num_2, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_3:
		_data.insert(make_pair(Keys::Num_3, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_4:
		_data.insert(make_pair(Keys::Num_4, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_5:
		_data.insert(make_pair(Keys::Num_5, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_6:
		_data.insert(make_pair(Keys::Num_6, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_7:
		_data.insert(make_pair(Keys::Num_7, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_8:
		_data.insert(make_pair(Keys::Num_8, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_9:
		_data.insert(make_pair(Keys::Num_9, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_ESCAPE:
		_data.insert(make_pair(Keys::Esc, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_MINUS:
		_data.insert(make_pair(Keys::Minus, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_EQUAL:
		_data.insert(make_pair(Keys::Plus, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_PERIOD:
		_data.insert(make_pair(Keys::Period, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_SPACE:
		_data.insert(make_pair(Keys::Space, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_ENTER:
		_data.insert(make_pair(Keys::Enter, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_BACKSPACE:
		_data.insert(make_pair(Keys::Backspace, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_TAB:
		_data.insert(make_pair(Keys::Tab, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_COMMA:
		_data.insert(make_pair(Keys::Less, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_SEMICOLON:
		_data.insert(make_pair(Keys::Colon, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_SLASH:
		_data.insert(make_pair(Keys::Question, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_BACKSLASH:
		_data.insert(make_pair(Keys::Backslash, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_DELETE:
		_data.insert(make_pair(Keys::Delete, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_LEFT_SHIFT:
		_data.insert(make_pair(Keys::Left_Shift, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_RIGHT_SHIFT:
		_data.insert(make_pair(Keys::Right_Shift, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_LEFT_ALT:
		_data.insert(make_pair(Keys::Left_Alt, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_RIGHT_ALT:
		_data.insert(make_pair(Keys::Right_Alt, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_LEFT_CONTROL:
		_data.insert(make_pair(Keys::Left_Ctrl, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_RIGHT_CONTROL:
		_data.insert(make_pair(Keys::Right_Ctrl, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_END:
		_data.insert(make_pair(Keys::End, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_HOME:
		_data.insert(make_pair(Keys::Home, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_INSERT:
		_data.insert(make_pair(Keys::Insert, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_PAGE_UP:
		_data.insert(make_pair(Keys::PageUp, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_PAGE_DOWN:
		_data.insert(make_pair(Keys::PageDown, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_UP:
		_data.insert(make_pair(Keys::Up, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_DOWN:
		_data.insert(make_pair(Keys::Down, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_RIGHT:
		_data.insert(make_pair(Keys::Right, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_LEFT:
		_data.insert(make_pair(Keys::Left, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_F1:
		_data.insert(make_pair(Keys::F1, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_F2:
		_data.insert(make_pair(Keys::F2, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_F3:
		_data.insert(make_pair(Keys::F3, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_F4:
		_data.insert(make_pair(Keys::F4, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_F5:
		_data.insert(make_pair(Keys::F5, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_F6:
		_data.insert(make_pair(Keys::F6, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_F7:
		_data.insert(make_pair(Keys::F7, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_F8:
		_data.insert(make_pair(Keys::F8, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_F9:
		_data.insert(make_pair(Keys::F9, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_F10:
		_data.insert(make_pair(Keys::F10, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_F11:
		_data.insert(make_pair(Keys::F11, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	case GLFW_KEY_F12:
		_data.insert(make_pair(Keys::F12, (action == GLFW_PRESS || action == GLFW_REPEAT) ? KeyState::State_Down : KeyState::State_Up));
		break;
	default:
		break;
	}
}