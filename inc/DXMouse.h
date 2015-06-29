#pragma once
#include "IMouse.h"
namespace Break{
	namespace Renderer{
		class DXManager;
	}
	namespace Input{
		class DXMouse : public Infrastructure::IMouse{
			friend class Renderer::DXManager;
		private:

			/**
			 * @fn	static void DXMouse::mouseButton(int button, int state);
			 *
			 * @brief	Mouse button.
			 *
			 * @author	Moustapha Saad
			 * @date	29/01/2015
			 *
			 * @param	button	The button.
			 * @param	state 	The state.
			 */

			static void mouseButton(int button, int state);

			/**
			 * @fn	static void DXMouse::mouseMove(int x, int y);
			 *
			 * @brief	Mouse move.
			 *
			 * @author	Moustapha Saad
			 * @date	29/01/2015
			 *
			 * @param	x	The x coordinate.
			 * @param	y	The y coordinate.
			 */

			static void mouseMove(int x, int y);

		protected:
			/**
			 * @fn	void DXMouse::update();
			 *
			 * @brief	Updates this object.
			 *
			 * @author	Moustapha Saad
			 * @date	29/01/2015
			 */

			void update();
		};
	}
}