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

			Texture();
			virtual ~Texture();

			Type getType();
		protected:
			Type _type;
			ImagePtr _image;

			virtual bool createGPUResource()=0;

		};
	}
}