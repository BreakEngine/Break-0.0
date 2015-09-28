#include "Texture2D.h"
#include "Engine.h"
#include "Image.h"
#include <Services.h>
using namespace Break::GXWrapper;

Texture2D::Texture2D(ImagePtr src,bool mipmaps):Texture(mipmaps){
	_type = TEXTURE2D;
	_image = src;
	createGPUResource();
}

Texture2D::~Texture2D(){
	//Engine delete texture
	//Infrastructure::Engine::Instance->GraphicsDevice->deleteTexture2D(this);
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::DEL;

	ins.args.push(Renderer::GPU_ISA::TEXTURE2D);
	ins.args.push(_handle.get());

	Services::getGPU_VM()->execute(ins);
}

void Texture2D::update(ImagePtr src){
	if(_image != src)
		_image = src;
	//Infrastructure::Engine::Instance->GraphicsDevice->updateTexture2D(this,*_image);
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::MAP;
	ins.args.push(Renderer::GPU_ISA::TEXTURE2D);
	ins.args.push(_handle.get());
	ins.args.push(_image.get());

	Services::getGPU_VM()->execute(ins);
}

ImagePtr Texture2D::readImage(){
	return _image;
}

void Texture2D::use(Shader::Type type,unsigned int unit){
	//Engine use texture
	//Infrastructure::Engine::Instance->GraphicsDevice->useTexture2D(this,unit,type);
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::BIND;
	ins.args.push(Renderer::GPU_ISA::TEXTURE2D);

	ins.args.push(_handle.get());

	if(type == Shader::Type::VERTEX)
		ins.args.push(Renderer::GPU_ISA::VERTEX_SHADER);
	else if(type == Shader::Type::PIXEL)
		ins.args.push(Renderer::GPU_ISA::PIXEL_SHADER);

	ins.args.push(unit);

	Services::getGPU_VM()->execute(ins);
}

bool Texture2D::createGPUResource(){
	//Engine create Texture
	//return Infrastructure::Engine::Instance->GraphicsDevice->createTexture2D(this,*_image);
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::GEN;

	ins.args.push(Renderer::GPU_ISA::TEXTURE2D);
	ins.args.push(_image.get());
	ins.args.push(_mipmaps);

	_handle = Services::getGPU_VM()->execute(ins);
	return true;
}