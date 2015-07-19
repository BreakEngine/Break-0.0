#include "ResourceManager.h"
#include <Image.h>
#include <FreeImage.h>
#include <Texture2D.h>
using namespace Break::GXWrapper;
using namespace std;

#pragma comment (lib, "FreeImage.lib")

map<string,IResourcePtr> ResourceManager::_resources = map<string,IResourcePtr>();

IResourcePtr ResourceManager::find(std::string name){
	auto res = _resources.find(name);
	if(res == _resources.end())
		return nullptr;
	else
		return res->second;
}

void ResourceManager::add(IResource* res){
	if(res){
		_resources[res->getName()] = IResourcePtr(res);
	}
}

void ResourceManager::add(std::string name, IResource* res)
{
	if(res){
		res->_name = name;
		_resources[res->getName()] = IResourcePtr(res);
	}
}

template<class T>
std::shared_ptr<T> ResourceManager::load(std::string file)
{
	return nullptr;
}

template<>
ImagePtr ResourceManager::load<Image>(std::string file){
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

	FIBITMAP* dib(0);

	BYTE* bits(0);

	unsigned int width(0), height(0);

	fif = FreeImage_GetFileType(file.c_str(),0);

	if(fif==FIF_UNKNOWN)
	{
		fif = FreeImage_GetFIFFromFilename(file.c_str());
	}

	if(fif == FIF_UNKNOWN)
	{
		return nullptr;
	}

	if(FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif,file.c_str());

	if(!dib)
		return nullptr;

	dib = FreeImage_ConvertTo32Bits(dib);
	bits = FreeImage_GetBits(dib);

	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	if((bits == 0)||(width == 0)||(height == 0))
		return nullptr;

	Pixel* p = reinterpret_cast<Pixel*>(bits);

	ImagePtr res = make_shared<Image>(reinterpret_cast<Pixel*>(bits),width,height);
	FreeImage_Unload(dib);
	return res;
}

template<>
Texture2DPtr ResourceManager::load<Texture2D>(std::string file)
{
	auto img = ResourceManager::load<Image>(file);
	return make_shared<Texture2D>(img);
}