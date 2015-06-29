#include "DXKeyboard.h"
#include <utility>
#include <windows.h>
using namespace Break::Input;
using namespace std;
void DXKeyboard::keyboardDown(unsigned int k){
	switch (k)
	{
	case 0x41:
		_data.insert(make_pair(Keys::A, KeyState::State_Down));
		break;
	case 0x42:
		_data.insert(make_pair(Keys::B, KeyState::State_Down));
		break;
	case 0x43:
		_data.insert(make_pair(Keys::C, KeyState::State_Down));
		break;
	case 0x44:
		_data.insert(make_pair(Keys::D, KeyState::State_Down));
		break;
	case 0x45:
		_data.insert(make_pair(Keys::E, KeyState::State_Down));
		break;
	case 0x46:
		_data.insert(make_pair(Keys::F, KeyState::State_Down));
		break;
	case 0x47:
		_data.insert(make_pair(Keys::G, KeyState::State_Down));
		break;
	case 0x48:
		_data.insert(make_pair(Keys::H, KeyState::State_Down));
		break;
	case 0x49:
		_data.insert(make_pair(Keys::I, KeyState::State_Down));
		break;
	case 0x4A:
		_data.insert(make_pair(Keys::J, KeyState::State_Down));
		break;
	case 0x4B:
		_data.insert(make_pair(Keys::K, KeyState::State_Down));
		break;
	case 0x4C:
		_data.insert(make_pair(Keys::L, KeyState::State_Down));
		break;
	case 0x4D:
		_data.insert(make_pair(Keys::M, KeyState::State_Down));
		break;
	case 0x4E:
		_data.insert(make_pair(Keys::N, KeyState::State_Down));
		break;
	case 0x4F:
		_data.insert(make_pair(Keys::O, KeyState::State_Down));
		break;
	case 0x50:
		_data.insert(make_pair(Keys::P, KeyState::State_Down));
		break;
	case 0x51:
		_data.insert(make_pair(Keys::Q, KeyState::State_Down));
		break;
	case 0x52:
		_data.insert(make_pair(Keys::R, KeyState::State_Down));
		break;
	case 0x53:
		_data.insert(make_pair(Keys::S, KeyState::State_Down));
		break;
	case 0x54:
		_data.insert(make_pair(Keys::T, KeyState::State_Down));
		break;
	case 0x55:
		_data.insert(make_pair(Keys::U, KeyState::State_Down));
		break;
	case 0x56:
		_data.insert(make_pair(Keys::V, KeyState::State_Down));
		break;
	case 0x57:
		_data.insert(make_pair(Keys::W, KeyState::State_Down));
		break;
	case 0x58:
		_data.insert(make_pair(Keys::X, KeyState::State_Down));
		break;
	case 0x59:
		_data.insert(make_pair(Keys::Y, KeyState::State_Down));
		break;
	case 0x5A:
		_data.insert(make_pair(Keys::Z, KeyState::State_Down));
		break;
	case 0x30:
		_data.insert(make_pair(Keys::Num_0, KeyState::State_Down));
		break;
	case 0x31:
		_data.insert(make_pair(Keys::Num_1, KeyState::State_Down));
		break;
	case 0x32:
		_data.insert(make_pair(Keys::Num_2, KeyState::State_Down));
		break;
	case 0x33:
		_data.insert(make_pair(Keys::Num_3, KeyState::State_Down));
		break;
	case 0x34:
		_data.insert(make_pair(Keys::Num_4, KeyState::State_Down));
		break;
	case 0x35:
		_data.insert(make_pair(Keys::Num_5, KeyState::State_Down));
		break;
	case 0x36:
		_data.insert(make_pair(Keys::Num_6, KeyState::State_Down));
		break;
	case 0x37:
		_data.insert(make_pair(Keys::Num_7, KeyState::State_Down));
		break;
	case 0x38:
		_data.insert(make_pair(Keys::Num_8, KeyState::State_Down));
		break;
	case 0x39:
		_data.insert(make_pair(Keys::Num_9, KeyState::State_Down));
		break;
	case 0x1B:
		_data.insert(make_pair(Keys::Esc, KeyState::State_Down));
		break;
	case 0xBD:
		_data.insert(make_pair(Keys::Minus, KeyState::State_Down));
		_data.insert(make_pair(Keys::Underscore, KeyState::State_Down));
		break;
	case 0xBC:
		_data.insert(make_pair(Keys::Comma, KeyState::State_Down));
		_data.insert(make_pair(Keys::Less, KeyState::State_Down));
		break;
	case 0xBB:
		_data.insert(make_pair(Keys::Plus, KeyState::State_Down));
		_data.insert(make_pair(Keys::Equals, KeyState::State_Down));
		break;
	case 0xBE:
		_data.insert(make_pair(Keys::Period, KeyState::State_Down));
		_data.insert(make_pair(Keys::Greater, KeyState::State_Down));
		break;
	case 0x20:
		_data.insert(make_pair(Keys::Space, KeyState::State_Down));
		break;
	case 0x0D:
		_data.insert(make_pair(Keys::Enter, KeyState::State_Down));
		break;
	case 0x08:
		_data.insert(make_pair(Keys::Backspace, KeyState::State_Down));
		break;
	case 0x09:
		_data.insert(make_pair(Keys::Tab, KeyState::State_Down));
		break;
	case 0xBF:
		_data.insert(make_pair(Keys::Question, KeyState::State_Down));
		break;
	case 0xE2:
		_data.insert(make_pair(Keys::Backslash, KeyState::State_Down));
		break;
	case 0x2E:
		_data.insert(make_pair(Keys::Delete, KeyState::State_Down));
		break;
	case 0xA0:
		_data.insert(make_pair(Keys::Left_Shift, KeyState::State_Down));
		break;
	case 0xA1:
		_data.insert(make_pair(Keys::Right_Shift, KeyState::State_Down));
		break;
	case 0x12:
		_data.insert(make_pair(Keys::Left_Alt, KeyState::State_Down));
		_data.insert(make_pair(Keys::Right_Alt, KeyState::State_Down));
		break;
	case 0xA2:
		_data.insert(make_pair(Keys::Left_Ctrl, KeyState::State_Down));
		break;
	case 0xA3:
		_data.insert(make_pair(Keys::Right_Ctrl, KeyState::State_Down));
		break;
	case 0x23:
		_data.insert(make_pair(Keys::End, KeyState::State_Down));
		break;
	case 0x24:
		_data.insert(make_pair(Keys::Home, KeyState::State_Down));
		break;
	case 0x2D:
		_data.insert(make_pair(Keys::Insert, KeyState::State_Down));
		break;
	case 0x21:
		_data.insert(make_pair(Keys::PageUp, KeyState::State_Down));
		break;
	case 0x22:
		_data.insert(make_pair(Keys::PageDown, KeyState::State_Down));
		break;
	case 0x26:
		_data.insert(make_pair(Keys::Up, KeyState::State_Down));
		break;
	case 0x28:
		_data.insert(make_pair(Keys::Down, KeyState::State_Down));
		break;
	case 0x27:
		_data.insert(make_pair(Keys::Right, KeyState::State_Down));
		break;
	case 0x25:
		_data.insert(make_pair(Keys::Left, KeyState::State_Down));
		break;
	case 0x70:
		_data.insert(make_pair(Keys::F1, KeyState::State_Down));
		break;
	case 0x71:
		_data.insert(make_pair(Keys::F2, KeyState::State_Down));
		break;
	case 0x72:
		_data.insert(make_pair(Keys::F3, KeyState::State_Down));
		break;
	case 0x73:
		_data.insert(make_pair(Keys::F4, KeyState::State_Down));
		break;
	case 0x74:
		_data.insert(make_pair(Keys::F5, KeyState::State_Down));
		break;
	case 0x75:
		_data.insert(make_pair(Keys::F6, KeyState::State_Down));
		break;
	case 0x76:
		_data.insert(make_pair(Keys::F7, KeyState::State_Down));
		break;
	case 0x77:
		_data.insert(make_pair(Keys::F8, KeyState::State_Down));
		break;
	case 0x78:
		_data.insert(make_pair(Keys::F9, KeyState::State_Down));
		break;
	case 0x79:
		_data.insert(make_pair(Keys::F10, KeyState::State_Down));
		break;
	case 0x7A:
		_data.insert(make_pair(Keys::F11, KeyState::State_Down));
		break;
	case 0x7B:
		_data.insert(make_pair(Keys::F12, KeyState::State_Down));
		break;
	default:
		break;
	}
}
void DXKeyboard::keyboardUp(unsigned int k){
	switch (k)
	{
	case 0x41:
		_data.insert(make_pair(Keys::A, KeyState::State_Up));
		break;
	case 0x42:
		_data.insert(make_pair(Keys::B, KeyState::State_Up));
		break;
	case 0x43:
		_data.insert(make_pair(Keys::C, KeyState::State_Up));
		break;
	case 0x44:
		_data.insert(make_pair(Keys::D, KeyState::State_Up));
		break;
	case 0x45:
		_data.insert(make_pair(Keys::E, KeyState::State_Up));
		break;
	case 0x46:
		_data.insert(make_pair(Keys::F, KeyState::State_Up));
		break;
	case 0x47:
		_data.insert(make_pair(Keys::G, KeyState::State_Up));
		break;
	case 0x48:
		_data.insert(make_pair(Keys::H, KeyState::State_Up));
		break;
	case 0x49:
		_data.insert(make_pair(Keys::I, KeyState::State_Up));
		break;
	case 0x4A:
		_data.insert(make_pair(Keys::J, KeyState::State_Up));
		break;
	case 0x4B:
		_data.insert(make_pair(Keys::K, KeyState::State_Up));
		break;
	case 0x4C:
		_data.insert(make_pair(Keys::L, KeyState::State_Up));
		break;
	case 0x4D:
		_data.insert(make_pair(Keys::M, KeyState::State_Up));
		break;
	case 0x4E:
		_data.insert(make_pair(Keys::N, KeyState::State_Up));
		break;
	case 0x4F:
		_data.insert(make_pair(Keys::O, KeyState::State_Up));
		break;
	case 0x50:
		_data.insert(make_pair(Keys::P, KeyState::State_Up));
		break;
	case 0x51:
		_data.insert(make_pair(Keys::Q, KeyState::State_Up));
		break;
	case 0x52:
		_data.insert(make_pair(Keys::R, KeyState::State_Up));
		break;
	case 0x53:
		_data.insert(make_pair(Keys::S, KeyState::State_Up));
		break;
	case 0x54:
		_data.insert(make_pair(Keys::T, KeyState::State_Up));
		break;
	case 0x55:
		_data.insert(make_pair(Keys::U, KeyState::State_Up));
		break;
	case 0x56:
		_data.insert(make_pair(Keys::V, KeyState::State_Up));
		break;
	case 0x57:
		_data.insert(make_pair(Keys::W, KeyState::State_Up));
		break;
	case 0x58:
		_data.insert(make_pair(Keys::X, KeyState::State_Up));
		break;
	case 0x59:
		_data.insert(make_pair(Keys::Y, KeyState::State_Up));
		break;
	case 0x5A:
		_data.insert(make_pair(Keys::Z, KeyState::State_Up));
		break;
	case 0x30:
		_data.insert(make_pair(Keys::Num_0, KeyState::State_Up));
		break;
	case 0x31:
		_data.insert(make_pair(Keys::Num_1, KeyState::State_Up));
		break;
	case 0x32:
		_data.insert(make_pair(Keys::Num_2, KeyState::State_Up));
		break;
	case 0x33:
		_data.insert(make_pair(Keys::Num_3, KeyState::State_Up));
		break;
	case 0x34:
		_data.insert(make_pair(Keys::Num_4, KeyState::State_Up));
		break;
	case 0x35:
		_data.insert(make_pair(Keys::Num_5, KeyState::State_Up));
		break;
	case 0x36:
		_data.insert(make_pair(Keys::Num_6, KeyState::State_Up));
		break;
	case 0x37:
		_data.insert(make_pair(Keys::Num_7, KeyState::State_Up));
		break;
	case 0x38:
		_data.insert(make_pair(Keys::Num_8, KeyState::State_Up));
		break;
	case 0x39:
		_data.insert(make_pair(Keys::Num_9, KeyState::State_Up));
		break;
	case 0x1B:
		_data.insert(make_pair(Keys::Esc, KeyState::State_Up));
		break;
	case 0xBD:
		_data.insert(make_pair(Keys::Minus, KeyState::State_Up));
		_data.insert(make_pair(Keys::Underscore, KeyState::State_Up));
		break;
	case 0xBC:
		_data.insert(make_pair(Keys::Comma, KeyState::State_Up));
		_data.insert(make_pair(Keys::Less, KeyState::State_Up));
		break;
	case 0xBB:
		_data.insert(make_pair(Keys::Plus, KeyState::State_Up));
		_data.insert(make_pair(Keys::Equals, KeyState::State_Up));
		break;
	case 0xBE:
		_data.insert(make_pair(Keys::Period, KeyState::State_Up));
		_data.insert(make_pair(Keys::Greater, KeyState::State_Up));
		break;
	case 0x20:
		_data.insert(make_pair(Keys::Space, KeyState::State_Up));
		break;
	case 0x0D:
		_data.insert(make_pair(Keys::Enter, KeyState::State_Up));
		break;
	case 0x08:
		_data.insert(make_pair(Keys::Backspace, KeyState::State_Up));
		break;
	case 0x09:
		_data.insert(make_pair(Keys::Tab, KeyState::State_Up));
		break;
	case 0xBF:
		_data.insert(make_pair(Keys::Question, KeyState::State_Up));
		break;
	case 0xE2:
		_data.insert(make_pair(Keys::Backslash, KeyState::State_Up));
		break;
	case 0x2E:
		_data.insert(make_pair(Keys::Delete, KeyState::State_Up));
		break;
	case 0xA0:
		_data.insert(make_pair(Keys::Left_Shift, KeyState::State_Up));
		break;
	case 0xA1:
		_data.insert(make_pair(Keys::Right_Shift, KeyState::State_Up));
		break;
	case 0x12:
		_data.insert(make_pair(Keys::Left_Alt, KeyState::State_Up));
		_data.insert(make_pair(Keys::Right_Alt, KeyState::State_Up));
		break;
	case 0xA2:
		_data.insert(make_pair(Keys::Left_Ctrl, KeyState::State_Up));
		break;
	case 0xA3:
		_data.insert(make_pair(Keys::Right_Ctrl, KeyState::State_Up));
		break;
	case 0x23:
		_data.insert(make_pair(Keys::End, KeyState::State_Up));
		break;
	case 0x24:
		_data.insert(make_pair(Keys::Home, KeyState::State_Up));
		break;
	case 0x2D:
		_data.insert(make_pair(Keys::Insert, KeyState::State_Up));
		break;
	case 0x21:
		_data.insert(make_pair(Keys::PageUp, KeyState::State_Up));
		break;
	case 0x22:
		_data.insert(make_pair(Keys::PageDown, KeyState::State_Up));
		break;
	case 0x26:
		_data.insert(make_pair(Keys::Up, KeyState::State_Up));
		break;
	case 0x28:
		_data.insert(make_pair(Keys::Down, KeyState::State_Up));
		break;
	case 0x27:
		_data.insert(make_pair(Keys::Right, KeyState::State_Up));
		break;
	case 0x25:
		_data.insert(make_pair(Keys::Left, KeyState::State_Up));
		break;
	case 0x70:
		_data.insert(make_pair(Keys::F1, KeyState::State_Up));
		break;
	case 0x71:
		_data.insert(make_pair(Keys::F2, KeyState::State_Up));
		break;
	case 0x72:
		_data.insert(make_pair(Keys::F3, KeyState::State_Up));
		break;
	case 0x73:
		_data.insert(make_pair(Keys::F4, KeyState::State_Up));
		break;
	case 0x74:
		_data.insert(make_pair(Keys::F5, KeyState::State_Up));
		break;
	case 0x75:
		_data.insert(make_pair(Keys::F6, KeyState::State_Up));
		break;
	case 0x76:
		_data.insert(make_pair(Keys::F7, KeyState::State_Up));
		break;
	case 0x77:
		_data.insert(make_pair(Keys::F8, KeyState::State_Up));
		break;
	case 0x78:
		_data.insert(make_pair(Keys::F9, KeyState::State_Up));
		break;
	case 0x79:
		_data.insert(make_pair(Keys::F10, KeyState::State_Up));
		break;
	case 0x7A:
		_data.insert(make_pair(Keys::F11, KeyState::State_Up));
		break;
	case 0x7B:
		_data.insert(make_pair(Keys::F12, KeyState::State_Up));
		break;
	default:
		break;
	}
}

void DXKeyboard::update(){
	IKeyboard::_data.clear();
}