#pragma once
#include "IGXManager.h"
#include "Application.h"
#include <GL/glew.h>

namespace Break{
	namespace Renderer{
		class GLHandle;

		/**
		 * \brief OpenGL manager class that has the API specific code
		 * \author Moustapha Saad
		 */
		class GLManager:public Infrastructure::IGXManager{
		private:
			/**
			 * \brief applys filter to a texture based on our enums
			 * \param filter filter that will be applied
			 * \param mipmap true if using mipmaps
			 * \param target target of the texture that being used
			 * \author Moustapha Saad
			 */
			void applyFilter2D(GXWrapper::TextureFilter filter,bool mipmap,GLenum target);

			/**
			 * \brief converts from TextureAddressMode enum to OpenGL address mode
			 * \param mode mode being applied to texture
			 * \return OpenGL Flag
			 * \author Moustapha Saad
			 */
			int getAddressMode(GXWrapper::TextureAddressMode mode);

			/**
			 * \brief converts from enum of CompareFunction to OpenGL Flag
			 * \param func function that will be used
			 * \return OpenGL Flag
			 * \author Moustapha Saad
			 */
			int getCompareFunc(GXWrapper::CompareFunction func);

		public:

			///default constructor
			GLManager();

			//default destructor
			virtual ~GLManager();

			/**
			 * \brief initialize the OpenGL Context
			 * \param app application pointer to running app
			 * \return true if initialized successfully
			 * \author Mohammed A. Abdel-Nasser
			 */
			virtual bool init(Infrastructure::ApplicationPtr app) override;

			/**
			 * \brief starts the window loop
			 * \author Mohammed A. Abdel-Nasser
			 */
			virtual void start() override;

			/**
			 * \brief change the rasterization mode
			 * \param mode rasterization mode
			 * \author Moustapha Saad
			 */
			virtual void setRasterMode(Infrastructure::RasterMode mode);

			/**
			 * \brief change the culling mode of the api
			 * \param cull cull mode that will be used
			 * \author Moustapha Saad
			 */
			virtual void setCullMode(Infrastructure::CullMode cull);

			/**
			 * \brief clears all the buffers, color and depth
			 * \author Moustapha Saad
			 */
			virtual void clearBuffer() override;

			/**
			 * \brief swaps buffer
			 * \author Moustapha Saad
			 */
			virtual void swapBuffer() override;

			/**
			 * \brief sets cursor position to location
			 * \param val position of the cursor to be set to
			 * \author Moustapha Saad
			 */
			virtual void setCursorPostion(glm::uvec2 val) override;

			/**
			 * \brief creates vertex buffer, GL_ARRAY_BUFFER
			 * \param buffer vertex buffer pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool createVertexBuffer(Infrastructure::GPUResource* buffer) override;

			/**
			 * \brief creates index buffer, GL_ELEMENT_ARRAY_BUFFER
			 * \param buffer index buffer pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool createIndexBuffer(Infrastructure::GPUResource* buffer) override;

			/**
			 * \brief updates vertex buffer range, it performs map buffer range and memcpy
			 * \param buffer vertex buffer pointer
			 * \param offset offset of the buffer
			 * \param size size to be mapped
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool updateVertexBuffer(Infrastructure::GPUResource* buffer, unsigned int offset, unsigned int size) override;

			/**
			 * \brief updates index buffer range, it performs map buffer range and memcpy
			 * \param buffer index buffer pointer
			 * \param offset offset of the buffer
			 * \param size size to be mapped
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool updateIndexBuffer(Infrastructure::GPUResource* buffer, uint offset, uint size) override;

			/**
			 * \brief deletes a buffer
			 * \param buffer buffer pointer
			 * \author Moustapha Saad
			 */
			virtual bool deleteBuffer(Infrastructure::GPUResource* buffer) override;

			/**
			 * \brief binds buffer to context
			 * \param buffer index buffer pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool useIndexBuffer(Infrastructure::GPUResource* buffer) override;

			/**
			 * \brief binds buffer to context
			 * \param buffer vertex buffer pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool useVertexBuffer(Infrastructure::GPUResource*)override;

			/**
			 * \brief create uniform buffer GL_UNIFORM_BUFFER
			 * \param buffer uniform buffer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool createUniformBuffer(Infrastructure::GPUResource* buffer)override;

			/**
			 * \brief updates buffer range, it performs map buffer range and memcpy
			 * \param buffer buffer pointer
			 * \param offset offset of the buffer
			 * \param size size to be mapped
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool updateUniformBuffer(Infrastructure::GPUResource* buffer,unsigned int offset,unsigned int size)override;

			/**
			 * \brief binds uniform buffer to context
			 * \param buffer buffer pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool useUniformBuffer(Infrastructure::GPUResource* buffer)override;

			/**
			 * \brief creates a shader program
			 * \param shader shader pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool createShader(Infrastructure::GPUResource* shader) override;

			/**
			 * \brief binds a shader program to Context
			 * \param shader shader pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool useShader(Infrastructure::GPUResource* shader) override;

			/**
			 * \brief delets a shader program
			 * \param shader shader pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool deleteShader(Infrastructure::GPUResource* shader) override;

			/**
			 * \brief creates a texture2D
			 * \param texture texture pointer
			 * \param img image resource pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool createTexture2D(Infrastructure::GPUResource* texture,GXWrapper::Image& img) override;

			/**
			 * \brief updates a texture
			 * \param texture texture pointer
			 * \param img image resource pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool updateTexture2D(Infrastructure::GPUResource* texture,GXWrapper::Image& img) override;

			/**
			 * \brief deletes texture
			 * \param texture texture pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool deleteTexture2D(Infrastructure::GPUResource* texture) override;

			/**
			 * \brief binds a texture to unit and shader
			 * \param texture texture pointer
			 * \param unit texture unit
			 * \param type shader type
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool useTexture2D(Infrastructure::GPUResource* texture, unsigned int unit, GXWrapper::Shader::Type type) override;

			/**
			 * \brief creates a geometry
			 * \param geometry pointer to geometry
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool createGeometry(GXWrapper::Geometry* geometry) override;

			/**
			 * \brief draws a geometry
			 * \param geometry pointer to geometry
			 * \param mode drawing mode
			 * \return true in case of success false otherwise
			 * \author Mohammed Shaalan
			 */
			virtual bool drawGeometry(GXWrapper::Geometry* geometry, GXWrapper::Primitive::Mode mode)override;

			/**
			 * \brief deletes a geometry
			 * \param geometry pointer to geometry
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool deleteGeometry(Infrastructure::GPUResource* geometry)override;

			/**
			 * \brief creates a sampler state
			 * \param state pointer to sampler
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool createSamplerState(Infrastructure::GPUResource* state)override;

			/**
			 * \brief binds sampler to context
			 * \param state pointer to sampler
			 * \param slot texture sampler slot
			 * \param type shader type
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool useSamplerState(Infrastructure::GPUResource* state,unsigned int slot, GXWrapper::Shader::Type type)override;

			/**
			 * \brief deletes a sampler state
			 * \param state pointer to sampler
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool deleteSamplerState(Infrastructure::GPUResource* state)override;

			/**
			 * \brief applies sampler state to texture
			 * \param sampler pointer to sampler
			 * \param texture pointer to texture
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool applySamplerStateToTexture2D(Infrastructure::GPUResource* sampler, Infrastructure::GPUResource* texture)override;

		};
	}
}
