#pragma once
#include<memory>
#include <glm/common.hpp>
#include "Application.h"
#include "GPUResource.h"
#include "GlobalDefinitions.h"
#include "Image.h"
#include "Shader.h"
#include "Geometry.h"

namespace Break{
	namespace Infrastructure{

		///raster modes
		enum class RasterMode
		{
			FILL=0, WIREFRAME
		};

		///cull modes
		enum class CullMode
		{
			NONE=0, FRONT, BACK
		};

		/**
		 * \brief graphics manager class that handles specific api code
		 * \author Moustapha Saad
		 */
		class IGXManager{
		protected:
		public:
			
			///default constructor
			IGXManager();
			///virtual destructor
			virtual ~IGXManager();

			/*!
			 * \function bool init()
			 *
			 * \brief initializes the graphics manager returns false if incounter errors
			 * \param app shared_ptr to application instance
			 *
			 * \author Moustapha Saad
			 */
			virtual bool init(ApplicationPtr app);

			/*!
			 * \function void start()
			 *
			 * \brief starts the graphics manager
			 *
			 * \author Moustapha Saad
			 */
			virtual void start();

			/**
			 * \brief changes the rasterizer mode
			 * \param mode choosen raster mode
			 * \author Moustapha Saad
			 */
			virtual void setRasterMode(RasterMode mode)=0;

			/**
			 * \brief changes cull mode
			 * \param mode choosen culling mode
			 * \author Moustapha Saad
			 */
			virtual void setCullMode(CullMode mode)=0;

			/*!
			 * \function void clearBuffer()
			 *
			 * \brief clears the buffers
			 *
			 * \author Moustapha Saad
			 */
			virtual void clearBuffer();

			/*!
			 * \function void swapBuffer()
			 *
			 * \brief swaps the buffer
			 *
			 * \author Moustapha Saad
			 */
			virtual void swapBuffer();

			/*!
			 * \function void setCursorPosition(glm::uvec2 val)
			 *
			 * \brief set cursor position based on the library used
			 * \param val cursor position
			 *
			 * \author Moustapha Saad
			 */
			virtual void setCursorPostion(glm::uvec2 val);

			/*!
			 * \function virtual bool createVertexBuffer(GPUResource*)
			 *
			 * \brief creates a vertex buffer
			 * \param buffer pointer to buffer instance
			 *
			 * \author Moustapha Saad
			 */
			virtual bool createVertexBuffer(GPUResource* buffer)=0;

			/*!
			 * \function virtual bool createIndexBuffer(GPUResource*)
			 *
			 * \brief creates an index buffer
			 * \param buffer pointer to buffer instance
			 *
			 * \author Moustapha Saad
			 */
			virtual bool createIndexBuffer(GPUResource* buffer)=0;

			/*!
			 * \function virtual bool useVertexBuffer(GPUResource*)
			 *
			 * \brief binds vertex buffer
			 * \param buffer pointer to buffer instance
			 *
			 * \author Moustapha Saad
			 */
			virtual bool useVertexBuffer(GPUResource* buffer)=0;

			/*!
			 * \function virtual bool useIndexBuffer(GPUResource*)
			 *
			 * \brief binds index buffer
			 * \param buffer pointer to buffer instance
			 *
			 * \author Moustapha Saad
			 */
			virtual bool useIndexBuffer(GPUResource* buffer)=0;

			/*!
			 * \function virtual bool updateVertexBuffer(GPUResource*)
			 *
			 * \brief updates the vertex buffer
			 * \param buffer pointer to buffer instance
			 * \param offset offset inside buffer memory to start with
			 * \param size size of the mapped range
			 *
			 * \author Moustapha Saad
			 */
			virtual bool updateVertexBuffer(GPUResource* buffer,uint offset,uint size)=0;

			/*!
			 * \function virtual bool updateIndexBuffer(GPUResource*, uint offset, uint size)
			 *
			 * \brief updates the index buffer
			 * \param buffer pointer to buffer instance
			 * \param offset offset inside buffer memory to start with
			 * \param size size of the mapped range
			 *
			 * \author Moustapha Saad
			 */
			virtual bool updateIndexBuffer(GPUResource* buffer, uint offset, uint size)=0;

			/*!
			 * \function virtual bool deleteBuffer(GPUResource*)
			 *
			 * \brief destroys the vertex buffer
			 * \param buffer pointer to buffer instance
			 *
			 * \author Moustapha Saad
			 */
			virtual bool deleteBuffer(GPUResource* buffer)=0;

			/*!
			 * \function virtual bool createUniformBuffer(GPUResource*)
			 *
			 * \brief creates uniform buffer
			 * \param buffer pointer to buffer instance
			 *
			 * \author Moustapha Saad
			 */
			virtual bool createUniformBuffer(GPUResource* buffer)=0;

			/*!
			 * \function virtual bool updateUniformBuffer(GPUResource*)
			 *
			 * \brief updates uniform buffer
			 * \param buffer pointer to buffer instance
			 * \param offset offset inside buffer memory to start with
			 * \param size size of the mapped range
			 *
			 * \author Moustapha Saad
			 */
			virtual bool updateUniformBuffer(GPUResource* buffer,unsigned int offset,unsigned int size)=0;

			/*!
			 * \function virtual bool useUniformBuffer(GPUResource*)
			 *
			 * \brief uses uniform buffer
			 * \param buffer pointer to buffer instance
			 *
			 * \author Moustapha Saad
			 */
			virtual bool useUniformBuffer(GPUResource* buffer)=0;


			/*!
			 * \function virtual bool createShader(GPUResource*)
			 * \brief creates a shader
			 * \param shader pointer to shader instance
			 * \author Moustapha Saad
			 */
			virtual bool createShader(GPUResource* shader)=0;

			/*!
			 * \function virtual bool useShader(GPUResource*)
			 * \brief uses a shader
			 * \param shader pointer to shader instance
			 * \author Moustapha Saad
			 */
			virtual bool useShader(GPUResource* shader)=0;

			/*!
			 * \function virtual bool deleteShader(GPUResource*)
			 * \brief deletes a shader
			 * \param shader pointer to shader instance
			 * \author Moustapha Saad
			 */
			virtual bool deleteShader(GPUResource* shader)=0;


			/**
			 * \brief creates a texture2D object
			 * \param tex pointer to texture instance
			 * \param img reference to image object
			 * \author Moustapha Saad
			 */
			virtual bool createTexture2D(GPUResource* tex, GXWrapper::Image& img)=0;

			/**
			 * \brief updates a texture2D object
			 * \param tex pointer to texture instance
			 * \param img reference to image object
			 * \author Moustapha Saad
			 */
			virtual bool updateTexture2D(GPUResource* tex, GXWrapper::Image& img)=0;

			/**
			 * \brief deletes a texture2D object
			 * \param tex pointer to texture instance
			 * \author Moustapha Saad
			 */
			virtual bool deleteTexture2D(GPUResource* tex)=0;

			/**
			 * \brief binds a texture2D object
			 * \param tex pointer to texture instance
			 * \param unit sampler unit in shader
			 * \param type type of the binded to shader
			 * \author Moustapha Saad
			 */
			virtual bool useTexture2D(GPUResource* tex, unsigned int unit, GXWrapper::Shader::Type type)=0;

			/**
			 * \brief creates a geometry object
			 * \param g pointer to geometry instance
			 * \author Moustapha Saad
			 */
			virtual bool createGeometry(GXWrapper::Geometry* g)=0;

			/**
			 * \brief draw a geometry object, performs a draw call
			 * \param g pointer to geometry instance
			 * \param mode drawing mode, normal, instanced, indexed .. etc
			 * \author Moustapha Saad
			 */
			virtual bool drawGeometry(GXWrapper::Geometry* g, GXWrapper::Primitive::Mode mode)=0;

			/**
			 * \brief deletes a geometry object
			 * \param g pointer to geometry instance
			 * \author Moustapha Saad
			 */
			virtual bool deleteGeometry(GPUResource* g)=0;

			/**
			 * \brief creates a sampler object
			 * \param s pointer to sampler instance
			 * \author Moustapha Saad
			 */
			virtual bool createSamplerState(GPUResource* s)=0;

			/**
			 * \brief binds a sampler object
			 * \param s pointer to sampler instance
			 * \param slot sampler unit in the shader
			 * \param type type of the binded to shader
			 * \author Moustapha Saad
			 */
			virtual bool useSamplerState(GPUResource* s,unsigned int slot, GXWrapper::Shader::Type type)=0;

			/**
			 * \brief deletes a sampler object
			 * \param s pointer to sampler instance
			 * \author Moustapha Saad
			 */
			virtual bool deleteSamplerState(GPUResource* s)=0;

			/**
			 * \brief applies a sampler object to texture
			 * \param sampler pointer to sampler instance
			 * \param texture pointer to texture instance
			 * \author Moustapha Saad
			 */
			virtual bool applySamplerStateToTexture2D(GPUResource* sampler,GPUResource* texture)=0;
		};
		///type alias to shared_ptr of IGXManager
		typedef std::shared_ptr<IGXManager> IGXManagerPtr;
	}
}