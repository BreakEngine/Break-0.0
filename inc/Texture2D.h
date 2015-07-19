#pragma once
#include "Texture.h"
#include "Image.h"
#include <memory>
#include "Shader.h"

namespace Break{
	namespace GXWrapper{
		class Texture2D:public Texture{
		public:
			Texture2D(ImagePtr src);
			~Texture2D();

			void update(ImagePtr src);

			Image& readImage();

			void use(Shader::Type,unsigned int unit=0);
		protected:
			virtual bool createGPUResource() override;
		};
		typedef std::shared_ptr<Texture2D> Texture2DPtr;
	}
}