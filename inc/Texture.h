#pragma once
#include "GPUResource.h"
#include "Image.h"

namespace Break{
	namespace GXWrapper{
		class Texture:public Infrastructure::GPUResource{
		public:
			enum Type{
				TEXTURE2D
			};

			Texture(bool mipmaps=false);
			virtual ~Texture();

			Type getType();

			bool usingMipMaps()
			{
				return _mipmaps;
			}
		protected:
			Type _type;
			ImagePtr _image;
			bool _mipmaps;

			virtual bool createGPUResource()=0;

		};
	}
}