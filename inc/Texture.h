#pragma once
#include "GPUResource.h"
#include "Image.h"
#include <memory>
#include "Shader.h"
#include "GlobalDefinitions.h"
namespace Break{
	namespace GXWrapper{

		/**
		 * \brief represents a generic texture object
		 */
		class BREAK_API_EX Texture:public Infrastructure::GPUResource{
			friend class Shader;
		public:

			///texture type
			enum Type{
				TEXTURE2D
			};

			/**
			 * \brief init constructor
			 * \param mipmaps true in case of using mipmaps
			 * \author Moustapha Saad
			 */
			Texture(bool mipmaps=false);
			virtual ~Texture();


			Type getType();

			///returns true if using mipmaps
			bool usingMipMaps()
			{
				return _mipmaps;
			}

			/**
			 * \brief binds a texture to shader sampler unit
			 * \param type shader type this texture will be binded to
			 * \param unit sampler unit to be binded to
			 * \author Moustapha Saad
			 */
			virtual void use(Shader::Type,unsigned int unit=0)=0;

			///updates the texture with an image and sync with GPU
			virtual void update(ImagePtr src)=0;

			///return width of the texture
			unsigned int getWidth();
			///return height of the texture
			unsigned int getHeight();
			///return depth of the texture
			unsigned int getDepth();

		protected:
			///texture type
			Type _type;
			///textreu image
			ImagePtr _image;
			///mipmaps flag
			bool _mipmaps;
			///applied sampler to this texture to avoid reapplying same sampler again
			SamplerState* sampler;

			///invoke create function to GPU
			virtual bool createGPUResource()=0;

		};
		typedef std::shared_ptr<Texture> TexturePtr;
	}
}