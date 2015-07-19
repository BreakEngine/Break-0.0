#pragma once
#include "Pixels.h"
#include "IResource.h"
#include <memory>

namespace Break{
	namespace GXWrapper{
		class Image:public IResource{

			Pixel* _data;

			unsigned int _width,_height,_depth,_dataSize;

			//To Prevent copying data
			Image(const Image& val);

		public:
			Image();
			Image(Pixel* data,unsigned int width,unsigned int height=1, unsigned int depth=1);
			Image(unsigned int width,unsigned int height=1, unsigned int depth=1);

			virtual ~Image();

			Pixel* getPixels();
			unsigned int getWidth();
			unsigned int getHeight();
			unsigned int getDepth();
			unsigned int getSize();

			void setWidth(unsigned int val);
			void setHeight(unsigned int val);
			void setDepth(unsigned int val);

			Pixel& getPixel(unsigned int x, unsigned int y=0, unsigned int z=0);

			std::shared_ptr<Image> clone();
		};
		typedef std::shared_ptr<Image> ImagePtr;

	}
}