#pragma once
#include <FreeImage.h>
#include <string>

namespace Break
{
	namespace GXWrapper
	{
		class Texture2D : public Infrastructure::GPUResource
		{
		private:
			std::string _filename;
			unsigned int _width;
			unsigned int _height;
			int _id;
			BYTE* _data;
			virtual bool createGPUResource()override;
		public:
			Texture2D(std::string filename, int id);
			virtual ~Texture2D();
			bool LoadTexture(std::string,int id);
			bool UseTexture();
			bool DeleteTexture();
			unsigned int getWidth();
			unsigned int getHeight();
			BYTE* getData();
			int getTexID();
		};
	}
}