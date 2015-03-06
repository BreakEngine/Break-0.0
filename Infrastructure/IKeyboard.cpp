#include"IKeyboard.h"
using namespace Break::Infrastructure;
using namespace std;
//init keyboard
map<IKeyboard::Keys, IKeyboard::KeyState> IKeyboard::_data = map<IKeyboard::Keys, IKeyboard::KeyState>();

IKeyboard::IKeyboard(){
	_data.clear();
}
IKeyboard::~IKeyboard(){
	//_data.clear();
}
IKeyboard::KeyState IKeyboard::getKey(IKeyboard::Keys key){
	auto it = _data.find(key);
	if (it == _data.end())
		return IKeyboard::KeyState::State_None;
	return it->second;
}

void IKeyboard::update(){

}