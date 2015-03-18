#pragma once
#include"../Infrastructure/IKeyboard.h"
namespace Break{
	namespace Renderer{
		class DXManager;
	}
	namespace Input{
		class DXKeyboard:public Infrastructure::IKeyboard{
			friend class Renderer::DXManager;
		private:

			/**
			 * @fn	static void DXKeyboard::keyboardDown(unsigned int k);
			 *
			 * @brief	Keyboard down.
			 *
			 * @author	Moustapha Saad
			 * @date	24/01/2015
			 *
			 * @param	k	The unsigned int of the down key.
			 */

			static void keyboardDown(unsigned int k);

			/**
			 * @fn	static void DXKeyboard::keyboardUp(unsigned int k);
			 *
			 * @brief	Keyboard up.
			 *
			 * @author	Moustapha Saad
			 * @date	24/01/2015
			 *
			 * @param	k	The unsigned int of the up key.
			 */

			static void keyboardUp(unsigned int k);
		protected:

			/**
			 * @fn	void DXKeyboard::update();
			 *
			 * @brief	Updates this object.
			 *
			 * @author	Moustapha Saad
			 * @date	24/01/2015
			 */

			void update();
		};
	}
}