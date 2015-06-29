#include "IAttribute.h"

using namespace glm;
using namespace Break::GXWrapper;
using namespace Break::Infrastructure;

IAttribute::IAttribute(){
	_data = NULL;
	_size = 0;
	isHandle = false;
}

IAttribute::IAttribute(int v){
	_size = sizeof(int);
	_data = new byte[_size];
	memcpy(_data,&v,_size);
	isHandle = false;
}

IAttribute::IAttribute(float v){
	_size = sizeof(float);
	_data = new byte[_size];
	memcpy(_data,&v,_size);
	isHandle = false;
}

IAttribute::IAttribute(double v){
	_size = sizeof(double);
	_data = new byte[_size];
	memcpy(_data,&v,_size);
	isHandle = false;
}

IAttribute::IAttribute(bool v){
	_size = sizeof(bool);
	_data = new byte[_size];
	memcpy(_data,&v,_size);
	isHandle = false;
}

IAttribute::IAttribute(vec2 v){
	_size = sizeof(vec2);
	_data = new byte[_size];
	memcpy(_data,&v,_size);
	isHandle = false;
}

IAttribute::IAttribute(vec3 v){
	_size = sizeof(vec3);
	_data = new byte[_size];
	memcpy(_data,&v,_size);
	isHandle = false;
}

IAttribute::IAttribute(vec4 v){
	_size = sizeof(vec4);
	_data = new byte[_size];
	memcpy(_data,&v,_size);
	isHandle = false;
}

IAttribute::IAttribute(const IAttribute& val){
	memcpy(_data,val._data,_size);
}

IAttribute::~IAttribute(){
	if(!isHandle)
		delete[] _data;
}

void IAttribute::clean(){
	_data = NULL;
}

IAttribute::operator int&(){
	return (int&)(*_data);
}

IAttribute::operator float&(){
	return (float&)(*_data);
}

IAttribute::operator double&(){
	return (double&)(*_data);
}

IAttribute::operator bool&(){
	return (bool&)(*_data);
}

IAttribute::operator vec2&(){
	return (vec2&)(*_data);
}

IAttribute::operator vec3&(){
	return (vec3&)(*_data);
}

IAttribute::operator vec4&(){
	return (vec4&)(*_data);
}

IAttribute& IAttribute::operator=(const IAttribute& val){
	memcpy(_data,val._data,_size);
	return *this;
}

unsigned int IAttribute::getSize(){
	return _size;
}

byte* IAttribute::getData(){
	return _data;
}