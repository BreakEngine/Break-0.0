#ifndef LIBRARY_BUILD
#pragma once
#include "Infrastructure.h"
#include "GXWrapper.h"
#include "TestVertex.h"
#include "VertexSet.h"
#include "Shader.h"
#include <iostream>
#include "ContentLoader.h"
#include "inc/Shape2D.h"
#include "SpriteBatch.h"
#include "inc/Sprite.h"
#include "Music.h"
#include "inc/Services.h"
#include "inc/GPUException.h"

using namespace std;
using namespace Break::Infrastructure;
using namespace Break::GXWrapper;
using namespace Break::Assets;

class spTest:public Break::Graphics::Sprite
{
public:
	spTest(Break::Graphics::SpriteBatch* sp,Texture2DPtr tex):Sprite(sp,tex)
	{
		
	}
};
class TestApp:public Application{
public:
	GeometryPtr moka;
	double scounter;
	Texture2DPtr tex,spTex;
	ShaderPtr shader;
	vec4 globalColor;
	Break::Graphics::SpritePtr all,mm;
	Break::Graphics::Shape2D wrect;
	std::vector<Break::Graphics::Shape2D> triangles;

	Break::Audio::MusicPtr forest;

	TestApp(){
		display = IDisplayPtr(new IDisplay(640,480,"Test Application"));
		scounter = 0;
	}
	~TestApp(){
	}
	void init(){
		Time::setFrameLimit(60);
		Time::setType(Time::Type::UNLIMITED);


		Application::init();
	}
	void testVM()
	{
		
	}
	void setupScene(){

		testVM();
		triangles.resize(1000);
		for(int i=0;i<1000;i++)
		{
			triangles[i].append(50,0);
			triangles[i].append(0,100);
			triangles[i].append(100,100);
			triangles[i].setPosition(rand()%640,rand()%480);
		}


		wrect.append(0,0);
		wrect.append(0,100);
		wrect.append(100,0);
		wrect.append(100,100);
		//wrect.append(-0.9,0);
		//wrect.append(0,0.9);
		wrect.setPosition(640/2,480/2);
		wrect.setFillColor(Color(255,0,0,255));

		forest = ContentLoader::load<Break::Audio::Music>("res//audio//forest.mp3");
		//forest->play();

		Application::setupScene();
	}
	void loadResources(){

		VertexSet<tv> veve(tv::getDeclaration());
		IndexSet soso;

		veve.append(tv(vec4(1,-1,1,1)*0.5f,vec4(1,0,0,1),vec2(1,1)));
		veve.append(tv(vec4(1,1,1,1)*0.5f,vec4(0,1,0,1),vec2(1,0)));
		veve.append(tv(vec4(-1,-1,1,1)*0.5f,vec4(0,0,1,1),vec2(0,1)));
		veve.append(tv(vec4(-1,1,1,1)*0.5f,vec4(1,0,1,1),vec2(0,0)));

		//Triangles
		soso.append(0);
		soso.append(1);
		soso.append(2);
		soso.append(2);
		soso.append(1);
		soso.append(3);


		moka = make_shared<Geometry>(veve,&soso,Primitive::TRIANGLES);

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
		if(Engine::Instance->getAPI()==API::OPENGL)
			shader = make_shared<Shader>(glVertex,glPixel,tv::getDeclaration());
		else
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
		spTex = ContentLoader::load<Texture2D>("res\\textures\\megaman.png");
		all = make_shared<Break::Graphics::Sprite>(spriteBatch,spTex);
		auto nullsp = make_shared<spTest>(spriteBatch,spTex);
		nullsp->setColor(Color(150,100,57,255));
		mm = make_shared<Break::Graphics::Sprite>(spriteBatch);
		mm->setSize(50,50);
		mm->setPosition(400,400);
		mm->setColor(Color(0,255,0,255));
		scene->addChild(mm);
		all->setSize(16,16);
		all->setPosition(200,200);
		scene->addChild(nullsp);
		scene->addChild(all);
		tex = make_shared<Texture2D>(loaded);
		shader->setTexture("diffuseS",tex.get());
		//tex->update(img);
		//tex->use(Shader::PIXEL,0);
		cout<<"moka moka"<<endl;
		Application::loadResources();
	}
	void cleanUp(){
		Application::cleanUp();
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
		if(IKeyboard::getKey(IKeyboard::Left) == IKeyboard::State_Down)
		{
			wrect.rotate(0.01);
		}
		if(IKeyboard::getKey(IKeyboard::Right) == IKeyboard::State_Down)
		{
			wrect.rotate(-0.01);
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
		
		Application::input();
	}
	void update(TimeStep time){
		wrect.rotate(time.delta*100);
		//cout<<Time::getFPS()<<endl;
		scounter+=time.delta;
		globalColor = vec4(sin(scounter),scounter,tan(scounter),1);
		//shader->setUniform("ucolor",&globalColor);
		if(scounter>=1){
			cout<<Time::getFPS()<<endl;
			scounter = 0;
		}
		Application::update(time);
	}
	void render(){
		//Engine::Instance->GraphicsDevice->setCullMode(CullMode::NONE);
		wrect.draw();
		/*
		for(int i=0;i<triangles.size();i++)
		{
			triangles[i].draw();
		}*/
		static float angle = 0;

		spriteBatch->begin();
		
		for(int i=0;i<0;i++)
			spriteBatch->draw(NULL,rand()%320,rand()%240,20,20,Color(255,0,0,255));
		for(int i=0;i<0;i++)
			spriteBatch->draw(tex.get(),rand()%320+320,rand()%240+240,10,10,Color(0,0,255,255));
		for(int i=0;i<0;i++)
			spriteBatch->draw(NULL, Break::Graphics::Rect(640/2,480/2,100,100),angle,Color(255,255,255,255));
		
		spriteBatch->draw(spTex.get(), Break::Graphics::Rect(420,50,32,32),Break::Graphics::Rect(0,16,16,16),0,Color(255,255,255,255));
		spriteBatch->draw(NULL, Break::Graphics::Rect(420,400,16,16),0,Color(255,255,255,127));
		//mm->draw();
		spriteBatch->end();
		//Engine::Instance->GraphicsDevice->setCullMode(CullMode::BACK);
		shader->use();
		shader->setTexture("diffuseS",tex.get());
		//tex->use(Shader::PIXEL,0);
		moka->draw();
		angle--;
		Application::render();
	}
};
#endif