#include "Image.h"

using namespace Break::GXWrapper;

Image::Image(){
	_type = IResource::IMAGE;
	_width = 0;
	_height = 0;
	_depth = 0;
	_data = NULL;
	_dataSize = 0;
}

Image::~Image(){
	if(_data)
		delete[] _data;
}

Image::Image(Pixel* data,unsigned int width,unsigned int height/* =1 */, unsigned int depth/* =1 */){
	_type = IResource::IMAGE;
	_width = width;
	_height = height;
	_depth = depth;
	_dataSize = _width*_height*_depth*sizeof(Pixel);
	_data = new Pixel[_dataSize];
	memcpy(_data,data,_dataSize);
}

Image::Image(unsigned int width,unsigned int height/* =1 */, unsigned int depth/* =1 */){
	_type = IResource::IMAGE;
	_width = width;
	_height = height;
	_depth = depth;

	_dataSize = _width *_height * _depth*sizeof(Pixel);
	_data= new Pixel[_dataSize];
}

Pixel* Image::getPixels(){
	return _data;
}

unsigned int Image::getWidth(){
	return _width;
}

unsigned int Image::getHeight(){
	return _height;
}

unsigned int Image::getDepth(){
	return _depth;
}

unsigned Image::getSize()
{
	return _dataSize;
}

void Image::setWidth(unsigned int val){
	_width = val;
}

void Image::setHeight(unsigned int val){
	_height = val;
}

void Image::setDepth(unsigned int val){
	_depth = val;
}

Pixel& Image::getPixel(unsigned int x,unsigned int y, unsigned int z){
	unsigned long ix = x+_width *(y+_depth*z);
	return _data[ix];
}

ImagePtr Image::clone(){
	Pixel* newData = NULL;
	memcpy(newData,_data,_dataSize);
	return std::make_shared<Image>(newData,_width,_height,_depth);
}