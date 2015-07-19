#pragma once
#include "Infrastructure.h"
#include "GXWrapper.h"
#include "TestVertex.h"
#include "VertexSet.h"
#include "Shader.h"
#include <iostream>

using namespace std;
using namespace Break::Infrastructure;
using namespace Break::GXWrapper;

class TestApp:public Application{
public:
	GeometryPtr moka;
	double scounter;
	Texture2DPtr tex;
	ShaderPtr shader;
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

		veve.append(tv(vec4(1,-1,0,1),vec4(1,0,0,1)));
		veve.append(tv(vec4(0,1,0,1),vec4(0,1,0,1)));
		veve.append(tv(vec4(-1,-1,0,1),vec4(0,0,1,1)));

		soso.append(0);
		soso.append(1);
		soso.append(2);

		moka = make_shared<Geometry>(&veve,&soso,Primitive::TRIANGLES);

		std::string glVertex = "#version 330\n"
			"layout(location = 0) in vec4 position;\n"
			"layout(location = 1) in vec4 color;\n"
			"uniform MatrixBuffer{\n"
			"mat4 worldMatrix;\n"
			"mat4 viewMatrix;\n"
			"mat4 projectionMatrix;\n"
			"};\n"
			"out vec4 ocolor;\n"
			"void main(){\n"
			"ocolor = color;\n"
			"gl_Position = position;\n"
			"}\n"
			;
		std::string glPixel = "#version 330\n"
			"in vec4 ocolor;\n"
			"uniform sampler2D diffuse;\n"
			"void main(){\n"
			"gl_FragColor = ocolor;\n"
			"}\n"
			;
		std::string dxVertex = "struct VertexInputType\n"
		"{\n"
			"float4 position : POSITION;\n"
			"float4 color : COLOR;\n"
		"};\n"

		"struct PixelInputType\n"
		"{\n"
			"float4 position : SV_POSITION;\n"
			"float4 color : COLOR;\n"
		"};\n"
		"cbuffer MatrixBuffer\n"
		"{\n"
			"matrix worldMatrix;\n"
			"matrix viewMatrix;\n"
			"matrix projectionMatrix;\n"
		"};\n"
		"PixelInputType main(VertexInputType input)\n"
		"{\n"
			"PixelInputType output;\n"


			// Change the position vector to be 4 units for proper matrix calculations.
			"input.position.w = 1.0f;\n"

			// Calculate the position of the vertex against the world, view, and projection matrices.
			//"output.position = mul(input.position, worldMatrix);\n"
			//"output.position = mul(output.position, viewMatrix);\n"
			//"output.position = mul(output.position, projectionMatrix);\n"
			"output.position = input.position;\n"

			// Store the input color for the pixel shader to use.
			"output.color = input.color;\n"

			"return output;\n"
		"}\n";

		std::string dxPixel = "struct PixelInputType\n"
		"{\n"
			"float4 position : SV_POSITION;\n"
			"float4 color : COLOR;\n"
		"};\n"
		"float4 main(PixelInputType input) : SV_TARGET\n"
		"{\n"
		"return input.color;\n"
		"}\n";

		shader = make_shared<Shader>(dxVertex,dxPixel,tv::getDeclaration());
		shader->registerUniformBlock("MatrixBuffer",3*64,0,Shader::VERTEX);
		shader->registerUniform("worldMatrix","MatrixBuffer",0,64);
		unsigned char world[64] = {'H'};
		shader->setUniform("worldMatrix",world);
		cout<<"HONE"<<endl;
		//shader->use();

		ImagePtr img = make_shared<Image>(512,512);
		Pixel white = {255,255,255,255};
		Pixel red = {255,0,0,255};
		cout<<sizeof(Pixel)<<endl;
		for(int i=0;i<512;i++)
			for(int j=0;j<512;j++){
				img->getPixel(i,j) = red;
			}

		ImagePtr loaded = ResourceManager::load<Image>("res\\textures\\grass.jpg");
		tex = make_shared<Texture2D>(loaded);
		//tex->update(img);
		//tex->use(Shader::PIXEL,0);
		cout<<"moka moka"<<endl;
	}
	void cleanUp(){

	}
	void input(){
		//getting mouse position
		auto mpos = IMouse::getPosition();
		//cout<<mpos.x<<" "<<mpos.y<<endl;
		//A test
		if(IKeyboard::getKey(IKeyboard::A) == IKeyboard::State_Down){
			cout<<"A Pressed"<<endl;
			cout<<tex->readImage().getWidth()<<endl;
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
		shader->use();
		//tex->use(Shader::PIXEL,0);
		moka->draw(Primitive::INDEXED);
	}
};