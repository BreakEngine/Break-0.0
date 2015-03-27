#pragma once
#include "../Infrastructure/Application.h"
#include "../Infrastructure/Time.h"
#include "../Infrastructure/IKeyboard.h"
#include "../Infrastructure/IMouse.h"
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
		auto mpos = IMouse::getPosition();
		//cout<<mpos.x<<" "<<mpos.y<<endl;
		if(IKeyboard::getKey(IKeyboard::Right_Shift) == IKeyboard::State_Down){
			cout<<"A Pressed"<<endl;
		}
		if(IMouse::getButton(IMouse::Right_Button) == IMouse::State_Down)
			cout<<"Left"<<endl;
		if(IMouse::getButton(IMouse::Right_Button) == IMouse::State_Up)
			cout<<"Left"<<endl;
		if(mpos.y>100)
			IMouse::setPosition(glm::uvec2(0,0));
	}
	void update(TimeStep time){
		//cout<<Time::getFPS()<<endl;
	}
	void render(){

	}
};