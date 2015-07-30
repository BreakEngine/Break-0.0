#include "Texture2D.h"
#include "Engine.h"
#include "Image.h"
using namespace Break::GXWrapper;

Texture2D::Texture2D(ImagePtr src,bool mipmaps):Texture(mipmaps){
	_type = TEXTURE2D;
	_image = src;
	createGPUResource();
}

Texture2D::~Texture2D(){
	//Engine delete texture
	Infrastructure::Engine::Instance->GraphicsDevice->deleteTexture2D(this);
}

void Texture2D::update(ImagePtr src){
	if(_image != src)
		_image = src;
	Infrastructure::Engine::Instance->GraphicsDevice->updateTexture2D(this,*_image);
}

ImagePtr Texture2D::readImage(){
	return _image;
}

void Texture2D::use(Shader::Type type,unsigned int unit){
	//Engine use texture
	Infrastructure::Engine::Instance->GraphicsDevice->useTexture2D(this,unit,type);
}

bool Texture2D::createGPUResource(){
	//Engine create Texture
	return Infrastructure::Engine::Instance->GraphicsDevice->createTexture2D(this,*_image);
}