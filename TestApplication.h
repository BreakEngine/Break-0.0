#pragma once
#include "Infrastructure.h"
#include "GXWrapper.h"
#include "TestVertex.h"
#include "VertexSet.h"
#include "Shader.h"
#include <iostream>
#include "ContentLoader.h"
#include "inc/Shape2D.h"

using namespace std;
using namespace Break::Infrastructure;
using namespace Break::GXWrapper;

class TestApp:public Application{
public:
	GeometryPtr moka;
	double scounter;
	Texture2DPtr tex;
	ShaderPtr shader;
	vec4 globalColor;

	Break::Renderer::Shape2D wrect;
	TestApp(){
		_display = IDisplayPtr(new IDisplay(640,480,"Test Application"));
		scounter = 0;
	}
	~TestApp(){

	}
	void init(){
		Time::setFrameLimit(60);
		Time::setType(Time::Type::UNLIMITED);

		
	}
	void setupScene(){

		wrect.append(0.75,-0.75);
		wrect.append(0.75,0.75);
		wrect.append(-0.75,-0.75);
		wrect.append(-0.75,0.75);
		wrect.append(-0.9,0);
		wrect.append(0,0.9);
		wrect.setFillColor(Color(255,255,0,255));
	}
	void loadResources(){

		VertexSet<tv> veve(tv::getDeclaration());
		IndexSet soso;

		veve.append(tv(vec4(1,-1,0,1)*0.5f,vec4(1,0,0,1),vec2(1,1)));
		veve.append(tv(vec4(1,1,0,1)*0.5f,vec4(0,1,0,1),vec2(1,0)));
		veve.append(tv(vec4(-1,-1,0,1)*0.5f,vec4(0,0,1,1),vec2(0,1)));
		veve.append(tv(vec4(-1,1,0,1)*0.5f,vec4(1,0,1,1),vec2(0,0)));

		//Triangles
		soso.append(0);
		soso.append(1);
		soso.append(2);
		soso.append(2);
		soso.append(1);
		soso.append(3);


		moka = make_shared<Geometry>(&veve,&soso,Primitive::TRIANGLES);

		std::string glVertex = "#version 330\n"
			"layout(location = 0) in vec4 position;\n"
			"layout(location = 1) in vec4 color;\n"
			"layout(location = 2) in vec2 tex;\n"
			"uniform MatrixBuffer{\n"
			"mat3 worldMatrix;\n"
			"vec4 ucolor;\n"
			"mat4 viewMatrix;\n"
			"mat4 projectionMatrix;\n"
			"};\n"
			"out vec4 ocolor;\n"
			"out vec2 otex;\n"
			"void main(){\n"
			"ocolor = ucolor;\n"
			"otex = tex;\n"
			"gl_Position = vec4(position.xyz,1);\n"
			"}\n"
			;
		std::string glPixel = "#version 330\n"
			"in vec4 ocolor;\n"
			"in vec2 otex;\n"
			"uniform sampler2D diffuseS;\n"
			"void main(){\n"
			"gl_FragColor = texture(diffuseS,otex);\n"
			"}\n"
			;
		std::string dxVertex = "struct VertexInputType\n"
		"{\n"
			"float4 position : POSITION;\n"
			"float4 color : COLOR;\n"
			"float2 tex : TEXCOORD0;\n"
		"};\n"

		"struct PixelInputType\n"
		"{\n"
			"float4 position : SV_POSITION;\n"
			"float4 color : COLOR;\n"
			"float2 tex : TEXCOORD0;\n"
		"};\n"
		"cbuffer MatrixBuffer\n"
		"{\n"
			"float3x3 worldMatrix;\n"
			"float4 ucolor;\n"
			"matrix viewMatrix;\n"
			"matrix projectionMatrix;\n"
		"};\n"
		"PixelInputType main(VertexInputType input)\n"
		"{\n"
			"PixelInputType output;\n"


			// Change the position vector to be 4 units for proper matrix calculations.
			//"input.position.w = 1.0f;\n"

			// Calculate the position of the vertex against the world, view, and projection matrices.
			//"output.position = mul(input.position, worldMatrix);\n"
			//"output.position = mul(output.position, viewMatrix);\n"
			//"output.position = mul(output.position, projectionMatrix);\n"
			"output.position = float4(input.position.xyz,1);\n"

			// Store the input color for the pixel shader to use.
			"output.color = ucolor;\n"
			"output.tex = input.tex;\n"

			"return output;\n"
		"}\n";

		std::string dxPixel = "struct PixelInputType\n"
		"{\n"
			"float4 position : SV_POSITION;\n"
			"float4 color : COLOR;\n"
			"float2 tex : TEXCOORD0;\n"
		"};\n"
		"Texture2D shaderTexture;\n"
		"SamplerState diffuseS;\n"
		"float4 main(PixelInputType input) : SV_TARGET\n"
		"{\n"
		"float4 textureColor;\n"
		"textureColor = shaderTexture.Sample(diffuseS,input.tex);\n"
		"return textureColor;\n"
		"}\n";
		shader = make_shared<Shader>(dxVertex,dxPixel,tv::getDeclaration());
		shader->registerUniformBlock("MatrixBuffer",(2*64)+16+48,0,Shader::VERTEX);
		shader->registerUniform("worldMatrix","MatrixBuffer",0,36);
		shader->registerUniform("ucolor","MatrixBuffer",1*48,16);
		shader->registerSampler("diffuseS",0,make_shared<SamplerState>(),Shader::PIXEL);
		unsigned char world[64] = {'H'};
		shader->setUniform("worldMatrix",world);
		globalColor = vec4(1,1,1,1);
		shader->setUniform("ucolor",&globalColor);
		cout<<"HONE"<<endl;
		shader->use();

		ImagePtr img = make_shared<Image>(512,512);
		Pixel white = Pixel(255,255,255,255);
		Pixel red = Pixel(255,0,0,255);
		cout<<sizeof(Pixel)<<endl;
		for(int i=0;i<512;i++)
			for(int j=0;j<512;j++){
				img->getPixel(i,j) = red;
			}

		ImagePtr loaded = ContentLoader::load<Image>("res\\textures\\grass.jpg");
		tex = make_shared<Texture2D>(loaded);
		shader->setTexture("diffuseS",tex);
		//tex->update(img);
		//tex->use(Shader::PIXEL,0);
		cout<<"moka moka"<<endl;
	}
	void cleanUp(){

	}
	void randomizeTexture()
	{
		ImagePtr image = make_shared<Image>(512,512);
		for(int i=0;i<image->getWidth();i++)
		{
			for(int j=0;j<image->getHeight();j++)
			{
				image->getPixel(i,j) = Pixel(rand()%255,rand()%255,rand()%255,rand()%255);
				//image->getPixel(i,j) = Pixel(255,255,255,255);
			}
		}
		tex->update(image);
	}
	void input(){
		bool pressed = false;
		//getting mouse position
		auto mpos = IMouse::getPosition();
		//cout<<mpos.x<<" "<<mpos.y<<endl;
		//A test
		if(IKeyboard::getKey(IKeyboard::A) == IKeyboard::State_Down){
			cout<<"A Pressed"<<endl;
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
		if(IMouse::getButton(IMouse::Left_Button) == IMouse::State_Down){
			cout<<"Left Button Pressed"<<endl;
		}
		if((IMouse::getButton(IMouse::Left_Button) == IMouse::State_Up)){
			cout<<"Left Button Released"<<endl;
		}

		//closes when user press ESC
		if(IKeyboard::getKey(IKeyboard::Esc) == IKeyboard::State_Down)
			this->shutdown();
	}
	void update(TimeStep time){
		//cout<<Time::getFPS()<<endl;
		scounter+=time.delta;
		globalColor = vec4(sin(scounter),scounter,tan(scounter),1);
		//shader->setUniform("ucolor",&globalColor);
		if(scounter>=1){
			cout<<Time::getFPS()<<endl;
			scounter = 0;
		}
	}
	void render(){
		//Engine::Instance->GraphicsDevice->setCullMode(CullMode::NONE);
		wrect.draw();
		//Engine::Instance->GraphicsDevice->setCullMode(CullMode::BACK);
		shader->use();
		shader->setTexture("diffuseS",tex);
		//tex->use(Shader::PIXEL,0);
		moka->draw(Primitive::INDEXED);
	}
};