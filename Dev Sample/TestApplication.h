#pragma once
#include "../Infrastructure/Application.h"
using namespace Break::Infrastructure;
class TestApp:public Application{
public:
	TestApp(){
		_display = IDisplayPtr(new IDisplay());
	}
	~TestApp(){

	}
	void init(){

	}
	void setupScene(){

	}
	void loadResources(){

	}
	void cleanUp(){

	}
	void input(){

	}
	void update(TimeStep time){

	}
	void render(){

	}
};