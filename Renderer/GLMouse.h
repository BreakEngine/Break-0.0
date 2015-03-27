#pragma once
#include"../Infrastructure/IMouse.h"
#include <GLFW/glfw3.h>
namespace Break{
	namespace Renderer{
		class GLManager;
	}
	namespace Input{
		class GLMouse : public Infrastructure::IMouse{
			friend class Renderer::GLManager;
		private:

			/**
			 * @fn	static void GLMouse::keyboardDownFunc(unsigned char k, int x, int y);
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
			static void mouseFunc(GLFWwindow* window, int key, int scancode, int action);

			static void mouseMotion(GLFWwindow* window,double x, double y);
		protected:
			/**
			 * @fn	void GLMouse::update();
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