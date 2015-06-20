#pragma once
#include<memory>
#include <glm/common.hpp>
#include "Application.h"
#include "GPUResource.h"
#include "GlobalDefinitions.h"

namespace Break{
	namespace Infrastructure{
		//graphics manager abstract class that will handle APIs
		class IGXManager{
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
		};
		typedef std::shared_ptr<IGXManager> IGXManagerPtr;
	}
}