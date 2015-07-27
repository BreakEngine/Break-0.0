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