#include "ContentLoader.h"
#include <Image.h>
#include <FreeImage.h>
#include <Texture2D.h>
#include "Sound.h"
#include <Music.h>
#include <SoundEffect.h>
#include <iostream>
using namespace Break::GXWrapper;
using namespace Break::Assets;
using namespace std;

#pragma comment (lib, "FreeImage.lib")
template<class T>
std::shared_ptr<T> ContentLoader::load(std::string file)
{
	return nullptr;
}

namespace Break{
	namespace Assets{
		template<>
		std::shared_ptr<Image> ContentLoader::load<Image>(std::string file){
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
			//FreeImage_ConvertToRGBAF()
			dib = FreeImage_ConvertTo32Bits(dib);
			FreeImage_FlipVertical(dib);
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
        Texture2DPtr ContentLoader::load<Texture2D>(std::string file)
        {
            auto img = ContentLoader::load<Image>(file);
            return make_shared<Texture2D>(img);
        }

        template<>
        std::shared_ptr<Break::Audio::Music> ContentLoader::load<Break::Audio::Music>(std::string file)
        {
            auto music = Mix_LoadMUS(file.c_str());
            return make_shared<Audio::Music>(music);
        }

        template<>
        std::shared_ptr<Break::Audio::SoundEffect> ContentLoader::load<Break::Audio::SoundEffect>(std::string file)
        {
            return make_shared<Audio::SoundEffect>(Mix_LoadWAV(file.c_str()));
        }
	}
}