#include "IDisplay.h"
using namespace Break::Infrastructure;
using namespace std;
IDisplay::IDisplay(unsigned int x, unsigned int y, std::string t){
	_width = x;
	_height = y;
	_title = t;
}

IDisplay::~IDisplay(){

}
float IDisplay::aspectRatio(){
	return (float)_width/(float)_height;
}

unsigned int IDisplay::getWidth()const{
	return _width;
}
unsigned int IDisplay::getHeight()const{
	return _height;
}
string IDisplay::getTitle()const{
	return _title;
}
void IDisplay::setTitle(std::string val){
	_title = val;

}
void IDisplay::setWidth(unsigned int val){
	_width = val;
}
void IDisplay::setHeight(unsigned int val){
	_height = val;
}