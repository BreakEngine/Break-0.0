#pragma once
#include "Infrastructure.h"
#include "GXWrapper.h"
#include "TestVertex.h"
#include "VertexSet.h"
#include <iostream>

using namespace std;
using namespace Break::Infrastructure;
using namespace Break::GXWrapper;

class TestApp:public Application{
public:
	Geometry moka;
	double scounter;
	TestApp(){
		_display = IDisplayPtr(new IDisplay());
		scounter = 0;
	}
	~TestApp(){

	}
	void init(){
		//Time::setFrameLimit(41);
		Time::setType(Time::Type::UNLIMITED);

		
	}
	void setupScene(){

		
	}
	void loadResources(){

		VertexSet<tv> veve(tv::getDeclaration());
		IndexSet soso;

		for(int i=0;i<10;i++){
			veve.append(tv(i));
			soso.append(i);
		}

		moka = Geometry(&veve,&soso);


	}
	void cleanUp(){

	}

	void checkUp(){
		tv* head = moka.getVertices<tv>();
		int tvc = moka.getVerticesCount();

		cout<<"Vertices"<<endl;
		for(int i=0;i<tvc;i++)
			cout<<head[i]._a<<endl;

		unsigned int* ihead = moka.getIndices();
		int itvc = moka.getIndicesCount();

		cout<<"Indices"<<endl;
		for(int i=0;i<itvc;i++)
			cout<<ihead[i]<<endl;
	}
	void input(){
		//getting mouse position
		auto mpos = IMouse::getPosition();
		//cout<<mpos.x<<" "<<mpos.y<<endl;
		//A test
		if(IKeyboard::getKey(IKeyboard::A) == IKeyboard::State_Down){
			cout<<"A Pressed"<<endl;
			checkUp();
		}
		if(IKeyboard::getKey(IKeyboard::A) == IKeyboard::State_Up){
			cout<<"A Released"<<endl;
		}
		//Delete Test
		if(IKeyboard::getKey(IKeyboard::Delete) == IKeyboard::State_Down){
			cout<<"Delete Pressed"<<endl;
		}
		if(IKeyboard::getKey(IKeyboard::Delete) == IKeyboard::State_Up){
			cout<<"Delete Released"<<endl;
		}
		//mouse Right Button
		if(IMouse::getButton(IMouse::Right_Button) == IMouse::State_Down)
			cout<<"Right Button Pressed"<<endl;
		if(IMouse::getButton(IMouse::Right_Button) == IMouse::State_Up)
			cout<<"Right Button Released"<<endl;
		//mouse Left Button
		if(IMouse::getButton(IMouse::Left_Button) == IMouse::State_Down)
			cout<<"Left Button Pressed"<<endl;
		if(IMouse::getButton(IMouse::Left_Button) == IMouse::State_Up)
			cout<<"Left Button Released"<<endl;

		if(mpos.y>100)
			IMouse::setPosition(glm::uvec2(0,0));

		//closes when user press ESC
		if(IKeyboard::getKey(IKeyboard::Esc) == IKeyboard::State_Down)
			this->shutdown();
	}
	void update(TimeStep time){
		//cout<<Time::getFPS()<<endl;
		scounter+=time.delta;
		if(scounter>=1){
			cout<<Time::getFPS()<<endl;
			scounter = 0;
		}
	}
	void render(){

	}
};