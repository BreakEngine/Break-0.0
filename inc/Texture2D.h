#pragma once
#include "Texture.h"
#include "Image.h"
#include <memory>
#include "Shader.h"

namespace Break{
	namespace GXWrapper{
		class Texture2D:public Texture{
		public:
			Texture2D(ImagePtr src,bool mipmaps=false);
			~Texture2D();

			void update(ImagePtr src)override;

			ImagePtr readImage();

			void use(Shader::Type,unsigned int unit=0) override;
		protected:
			virtual bool createGPUResource() override;
		};
		typedef std::shared_ptr<Texture2D> Texture2DPtr;
	}
}