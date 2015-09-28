#pragma once
#include "IGXManager.h"
#include "Application.h"
#include <GL/glew.h>
#include "GlobalDefinitions.h"

namespace Break{
	namespace Renderer{
		class GLHandle;

		/**
		 * \brief OpenGL manager class that has the API specific code
		 * \author Moustapha Saad
		 */
		class BREAK_API_EX GLManager:public Infrastructure::IGXManager{
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
			virtual Infrastructure::IGPUHandlePtr vm_createVertexBuffer(Renderer::GPU_ISA type, u32 size, void* data) override;

			/**
			 * \brief creates index buffer, GL_ELEMENT_ARRAY_BUFFER
			 * \param buffer index buffer pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool createIndexBuffer(Infrastructure::GPUResource* buffer) override;
			virtual Infrastructure::IGPUHandlePtr vm_createIndexBuffer(Renderer::GPU_ISA type, u32 size, void* data) override;

			/**
			 * \brief updates vertex buffer range, it performs map buffer range and memcpy
			 * \param buffer vertex buffer pointer
			 * \param offset offset of the buffer
			 * \param size size to be mapped
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool updateVertexBuffer(Infrastructure::GPUResource* buffer, u32 offset, u32 size) override;
			virtual void vm_mapVertexBuffer(Infrastructure::IGPUHandle* handle, u32 size, void* data) override;

			/**
			 * \brief updates index buffer range, it performs map buffer range and memcpy
			 * \param buffer index buffer pointer
			 * \param offset offset of the buffer
			 * \param size size to be mapped
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool updateIndexBuffer(Infrastructure::GPUResource* buffer, u32 offset, u32 size) override;
			virtual void vm_mapIndexBuffer(Infrastructure::IGPUHandle* handle, u32 size, void* data)override;

			/**
			 * \brief deletes a buffer
			 * \param buffer buffer pointer
			 * \author Moustapha Saad
			 */
			virtual bool deleteBuffer(Infrastructure::GPUResource* buffer) override;
			virtual bool vm_deleteBuffer(Infrastructure::IGPUHandle* handle)override;

			/**
			 * \brief binds buffer to context
			 * \param buffer index buffer pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool useIndexBuffer(Infrastructure::GPUResource* buffer) override;
			virtual void vm_bindIndexBuffer(Infrastructure::IGPUHandle* _handle) override;

			/**
			 * \brief binds buffer to context
			 * \param buffer vertex buffer pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool useVertexBuffer(Infrastructure::GPUResource*)override;
			virtual void vm_bindVertexBuffer(Infrastructure::IGPUHandle* _handle, u32 stride)override;

			/**
			 * \brief create uniform buffer GL_UNIFORM_BUFFER
			 * \param buffer uniform buffer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool createUniformBuffer(Infrastructure::GPUResource* buffer)override;
			virtual Infrastructure::IGPUHandlePtr vm_createUniformBuffer(u32 size, void* data, u32 slot)override;

			/**
			 * \brief updates buffer range, it performs map buffer range and memcpy
			 * \param buffer buffer pointer
			 * \param offset offset of the buffer
			 * \param size size to be mapped
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool updateUniformBuffer(Infrastructure::GPUResource* buffer,u32 offset,u32 size)override;
			virtual void vm_mapUniformBuffer(Infrastructure::IGPUHandle* _handle,u32 size, void* data)override;

			/**
			 * \brief binds uniform buffer to context
			 * \param buffer buffer pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool useUniformBuffer(Infrastructure::GPUResource* buffer)override;
			virtual void vm_bindUniformBuffer(Infrastructure::IGPUHandle* _handle, Renderer::GPU_ISA shader, u32 slot)override;

			/**
			 * \brief creates a shader program
			 * \param shader shader pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool createShader(Infrastructure::GPUResource* shader) override;
			virtual Infrastructure::IGPUHandlePtr vm_createProgram(std::string vertex,std::string pixel, GXWrapper::MemoryLayout* inputLayout)override;

			/**
			 * \brief binds a shader program to Context
			 * \param shader shader pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool useShader(Infrastructure::GPUResource* shader) override;
			virtual void vm_bindShader(Infrastructure::IGPUHandle* _handle)override;

			/**
			 * \brief delets a shader program
			 * \param shader shader pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool deleteShader(Infrastructure::GPUResource* shader) override;
			virtual void vm_deleteShader(Infrastructure::IGPUHandle* _handle)override;

			/**
			 * \brief creates a texture2D
			 * \param texture texture pointer
			 * \param img image resource pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool createTexture2D(Infrastructure::GPUResource* texture,GXWrapper::Image& img) override;
			virtual Infrastructure::IGPUHandlePtr vm_createTexture2D(GXWrapper::Image& img, bool mipmaps)override;

			/**
			 * \brief updates a texture
			 * \param texture texture pointer
			 * \param img image resource pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool updateTexture2D(Infrastructure::GPUResource* texture,GXWrapper::Image& img) override;
			virtual void vm_mapTexture2D(Infrastructure::IGPUHandle* _handle, GXWrapper::Image& img)override;

			/**
			 * \brief deletes texture
			 * \param texture texture pointer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool deleteTexture2D(Infrastructure::GPUResource* texture) override;
			virtual void vm_deleteTexture2D(Infrastructure::IGPUHandle* _handle)override;

			/**
			 * \brief binds a texture to unit and shader
			 * \param texture texture pointer
			 * \param unit texture unit
			 * \param type shader type
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool useTexture2D(Infrastructure::GPUResource* texture, u32 unit, GXWrapper::Shader::Type type) override;
			virtual void vm_bindTexture2D(Infrastructure::IGPUHandle* _handle, Renderer::GPU_ISA type, u32 unit)override;

			/**
			 * \brief creates a geometry
			 * \param geometry pointer to geometry
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool createGeometry(GXWrapper::Geometry* geometry) override;
			virtual Infrastructure::IGPUHandlePtr
			vm_createGeometry(Infrastructure::IGPUHandle* vertex, Infrastructure::IGPUHandle* pixel, GXWrapper::MemoryLayout* input_layout)override;

			/**
			 * \brief draws a geometry
			 * \param geometry pointer to geometry
			 * \param mode drawing mode
			 * \return true in case of success false otherwise
			 * \author Mohammed Shaalan
			 */
			virtual bool drawGeometry(GXWrapper::Geometry* geometry, GXWrapper::Primitive::Mode mode)override;

			virtual void 
			vm_draw(GXWrapper::Primitive::Type type, Infrastructure::IGPUHandle* geometry,
			Infrastructure::IGPUHandle* vertex_buffer, u32 vertices_count,
			GXWrapper::MemoryLayout* input_layout)override;

			virtual void 
			vm_drawIndexed(GXWrapper::Primitive::Type type, Infrastructure::IGPUHandle* geometry,
			Infrastructure::IGPUHandle* vertex_buffer, Infrastructure::IGPUHandle* index_buffer,
			u32 indices_count, GXWrapper::MemoryLayout* input_layout)override;

			/**
			 * \brief deletes a geometry
			 * \param geometry pointer to geometry
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool deleteGeometry(Infrastructure::GPUResource* geometry)override;
			virtual void vm_deleteGeometry(Infrastructure::IGPUHandle* _handle)override;

			/**
			 * \brief creates a sampler state
			 * \param state pointer to sampler
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool createSamplerState(Infrastructure::GPUResource* state)override;
			virtual Infrastructure::IGPUHandlePtr vm_createSampleState(GXWrapper::TextureAddressMode U, GXWrapper::TextureAddressMode V,
				GXWrapper::TextureAddressMode W, GXWrapper::TextureFilter filter,
			    GXWrapper::CompareFunction func, GXWrapper::Color* color)override;
			/**
			 * \brief binds sampler to context
			 * \param state pointer to sampler
			 * \param slot texture sampler slot
			 * \param type shader type
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool useSamplerState(Infrastructure::GPUResource* state,u32 slot, GXWrapper::Shader::Type type)override;
			virtual void vm_bindSampler(Infrastructure::IGPUHandle* _handle, Renderer::GPU_ISA shader, u32 slot)override;

			/**
			 * \brief deletes a sampler state
			 * \param state pointer to sampler
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool deleteSamplerState(Infrastructure::GPUResource* state)override;
			virtual void vm_deleteSampler(Infrastructure::IGPUHandle* _handle)override;

			/**
			 * \brief applies sampler state to texture
			 * \param sampler pointer to sampler
			 * \param texture pointer to texture
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool applySamplerStateToTexture2D(Infrastructure::GPUResource* sampler, Infrastructure::GPUResource* texture)override;
			virtual void vm_applySamplerTexture2D(Infrastructure::IGPUHandle* sampler, Infrastructure::IGPUHandle* texture, bool mipmaps, GXWrapper::TextureAddressMode U,
			    GXWrapper::TextureAddressMode V, GXWrapper::TextureFilter filter, GXWrapper::CompareFunction func,
			    GXWrapper::Color border_color
				)override;

		};
	}
}
