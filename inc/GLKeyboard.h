#pragma once
#include"IKeyboard.h"
#include <GLFW/glfw3.h>
namespace Break{
	namespace Renderer{
		class GLManager;
	}
	namespace Input{
		class GLKeyboard : public Infrastructure::IKeyboard{
			friend class Renderer::GLManager;
		private:

			/**
			 * @fn	static void GLKeyboard::keyboardDownFunc(unsigned char k, int x, int y);
			 *
			 * @brief	Keyboard down function to indicate that a key is down at this moment
			 *
			 * @author	Moustapha Saad
			 * @date	23/01/2015
			 *
			 * @param	k	The unsigned char to process.
			 * @param	x	The x coordinate.
			 * @param	y	The y coordinate.
			 */
			static void keyboardFunc(GLFWwindow* window, int key, int scancode, int action, int mods);

		protected:
			/**
			 * @fn	void GLKeyboard::update();
			 *
			 * @brief	Updates this object and key pressing map.
			 *
			 * @author	Moustapha Saad
			 * @date	23/01/2015
			 */
			void update();
		};
	}
}