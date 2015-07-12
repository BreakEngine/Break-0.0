#include "Texture2D.h"
#include "Engine.h"
Texture2D::Texture2D(std::string filename, int id)
{
	_filename = filename;
	_id = id;
	_data = 0;
	_width = 0;
	_height = 0;
}

bool Texture2D::createGPUResource()
{
	return Break::Infrastructure::Engine::Instance->GraphicsDevice->createTexture2D(this);
}

bool Texture2D::LoadTexture(std::string filename,int id)
{
	_filename = filename;
	_id = id;
	_data = 0;
	_width = 0;
	_height = 0;
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib = 0;
	fif = FreeImage_GetFileType(filename, 0);
	if(fif == FIF_UNKNOWN) 
		fif = FreeImage_GetFIFFromFilename(filename);
	if(fif == FIF_UNKNOWN)
		return false;
	if(FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	if(!dib)
		return false;

	_data = FreeImage_GetBits(dib);
	_width = FreeImage_GetWidth(dib);
	_height = FreeImage_GetHeight(dib);
	if((_data == 0) || (_width == 0) || (_height == 0))
		return false;
	return createGPUResource();
}

bool Texture2D::UseTexture()
{
	return Break::Infrastructure::Engine::Instance->GraphicsDevice->useTexture2D(this);
}

bool Texture2D::DeleteTexture()
{
	return Break::Infrastructure::Engine::Instance->GraphicsDevice->deleteTexture2D(this);
}

unsigned int Texture2D::getWidth()
{
	return _width;
}

unsigned int Texture2D::getHeight()
{
	return _height;
}

BYTE* Texture2D::getData()
{
	return _data;
}

int Texture2D::getTexID()
{
	return _id;
}
