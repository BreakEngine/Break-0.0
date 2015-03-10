#pragma once
#include<memory>
#include <glm/common.hpp>
#include "Application.h"
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

		};
		typedef std::shared_ptr<IGXManager> IGXManagerPtr;
	}
}