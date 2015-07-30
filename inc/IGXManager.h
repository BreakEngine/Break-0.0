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
		//graphics manager abstract class that will handle APIs

		enum class RasterMode
		{
			FILL=0, WIREFRAME
		};

		enum class CullMode
		{
			NONE=0, FRONT, BACK
		};
		class IGXManager{
		protected:
		public:
			
			//default constructor
			IGXManager();
			//virtual destructor
			virtual ~IGXManager();

			/*!
			 * \function bool init()
			 *
			 * \brief initializes the graphics manager returns false if incounter errors
			 *
			 * \author Moustapha Saad
			 */
			virtual bool init(ApplicationPtr);

			/*!
			 * \function void start()
			 *
			 * \brief starts the graphics manager
			 *
			 * \author Moustapha Saad
			 */
			virtual void start();

			virtual void setRasterMode(RasterMode)=0;

			virtual void setCullMode(CullMode)=0;

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
			 *
			 * \author Moustapha Saad
			 */
			virtual void setCursorPostion(glm::uvec2 val);

			/*!
			 * \function virtual bool createVertexBuffer(GPUResource*)
			 *
			 * \brief creates a vertex buffer
			 *
			 * \author Moustapha Saad
			 */
			virtual bool createVertexBuffer(GPUResource*)=0;

			/*!
			 * \function virtual bool createIndexBuffer(GPUResource*)
			 *
			 * \brief creates an index buffer
			 *
			 * \author Moustapha Saad
			 */
			virtual bool createIndexBuffer(GPUResource*)=0;

			/*!
			 * \function virtual bool useVertexBuffer(GPUResource*)
			 *
			 * \brief binds vertex buffer
			 *
			 * \author Moustapha Saad
			 */
			virtual bool useVertexBuffer(GPUResource*)=0;

			/*!
			 * \function virtual bool useIndexBuffer(GPUResource*)
			 *
			 * \brief binds index buffer
			 *
			 * \author Moustapha Saad
			 */
			virtual bool useIndexBuffer(GPUResource*)=0;

			/*!
			 * \function virtual bool updateVertexBuffer(GPUResource*)
			 *
			 * \brief updates the vertex buffer
			 *
			 * \author Moustapha Saad
			 */
			virtual bool updateVertexBuffer(GPUResource*,uint offset,uint size)=0;

			/*!
			 * \function virtual bool updateIndexBuffer(GPUResource*, uint offset, uint size)
			 *
			 * \brief updates the index buffer
			 *
			 * \author Moustapha Saad
			 */
			virtual bool updateIndexBuffer(GPUResource* buffer, uint offset, uint size)=0;

			/*!
			 * \function virtual bool deleteBuffer(GPUResource*)
			 *
			 * \brief destroys the vertex buffer
			 *
			 * \author Moustapha Saad
			 */
			virtual bool deleteBuffer(GPUResource*)=0;

			/*!
			 * \function virtual bool createUniformBuffer(GPUResource*)
			 *
			 * \brief creates uniform buffer
			 *
			 * \author Moustapha Saad
			 */
			virtual bool createUniformBuffer(GPUResource*)=0;

			/*!
			 * \function virtual bool updateUniformBuffer(GPUResource*)
			 *
			 * \brief updates uniform buffer
			 *
			 * \author Moustapha Saad
			 */
			virtual bool updateUniformBuffer(GPUResource*,unsigned int,unsigned int)=0;

			/*!
			 * \function virtual bool useUniformBuffer(GPUResource*)
			 *
			 * \brief uses uniform buffer
			 *
			 * \author Moustapha Saad
			 */
			virtual bool useUniformBuffer(GPUResource*)=0;


			/*!
			 * \function virtual bool createShader(GPUResource*)
			 * \brief creates a shader
			 * \author Moustapha Saad
			 */
			virtual bool createShader(GPUResource*)=0;

			/*!
			 * \function virtual bool useShader(GPUResource*)
			 * \brief uses a shader
			 * \author Moustapha Saad
			 */
			virtual bool useShader(GPUResource*)=0;

			/*!
			 * \function virtual bool deleteShader(GPUResource*)
			 * \brief deletes a shader
			 * \author Moustapha Saad
			 */
			virtual bool deleteShader(GPUResource*)=0;


			//texture functions
			virtual bool createTexture2D(GPUResource*, GXWrapper::Image&)=0;
			virtual bool updateTexture2D(GPUResource*, GXWrapper::Image&)=0;
			virtual bool deleteTexture2D(GPUResource*)=0;
			virtual bool useTexture2D(GPUResource*, unsigned int unit, GXWrapper::Shader::Type)=0;

			//geometry functions
			virtual bool createGeometry(GXWrapper::Geometry*)=0;
			virtual bool drawGeometry(GXWrapper::Geometry*, GXWrapper::Primitive::Mode mode)=0;
			virtual bool deleteGeometry(GPUResource*)=0;

			//sampler functions
			virtual bool createSamplerState(GPUResource*)=0;
			virtual bool useSamplerState(GPUResource*,unsigned int slot, GXWrapper::Shader::Type)=0;
			virtual bool deleteSamplerState(GPUResource*)=0;
			virtual bool applySamplerStateToTexture2D(GPUResource* sampler,GPUResource* texture)=0;
		};
		typedef std::shared_ptr<IGXManager> IGXManagerPtr;
	}
}