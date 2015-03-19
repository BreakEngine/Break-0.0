#pragma once
#include "../Infrastructure/Application.h"
#include "../Infrastructure/Time.h"
#include <iostream>
using namespace std;
using namespace Break::Infrastructure;
class TestApp:public Application{
public:
	TestApp(){
		_display = IDisplayPtr(new IDisplay());
	}
	~TestApp(){

	}
	void init(){
		Time::setFrameLimit(100);
		Time::setType(Time::Type::UNLIMITED);
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
		//cout<<Time::getFPS()<<endl;
	}
	void render(){

	}
};