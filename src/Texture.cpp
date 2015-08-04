#include "Texture.h"

using namespace Break::GXWrapper;

Texture::Texture(bool mipmaps):_mipmaps(mipmaps){
	_image = nullptr;
}

Texture::~Texture(){
	_image = nullptr;
}

Texture::Type Texture::getType(){
	return _type;
}

unsigned Texture::getWidth()
{
	if(_image)
		return _image->getWidth();
	else
		return 0;
}

unsigned Texture::getHeight()
{
	if(_image)
		return _image->getHeight();
	else
		return 0;
}

unsigned Texture::getDepth()
{
	if(_image)
		return _image->getDepth();
	else
		return 0;
}