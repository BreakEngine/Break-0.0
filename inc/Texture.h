#pragma once
#include "GPUResource.h"
#include "Image.h"
#include <memory>
#include "Shader.h"

namespace Break{
	namespace GXWrapper{
		class Texture:public Infrastructure::GPUResource{
			friend class Shader;
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

			virtual void use(Shader::Type,unsigned int unit=0)=0;
			virtual void update(ImagePtr src)=0;

		protected:
			Type _type;
			ImagePtr _image;
			bool _mipmaps;
			SamplerState* sampler;

			virtual bool createGPUResource()=0;

		};
		typedef std::shared_ptr<Texture> TexturePtr;
	}
}