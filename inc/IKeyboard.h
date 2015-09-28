#pragma once
#include<map>
#include<memory>
#include "InputDevice.h"
#include "GlobalDefinitions.h"

namespace Break{
	namespace Infrastructure{
		class BREAK_API_EX IKeyboard:public InputDevice{
		public:
			virtual ~IKeyboard();

			/**
			 * @enum	KeyState
			 *
			 * @brief	Values that represent key states.
			 */

			enum KeyState{
				State_Down, State_Up, State_None
			};

			/**
			 * @enum	Keys
			 *
			 * @brief	Values that represent keys.
			 */

			enum Keys{
				Backspace,
				Tab,
				Enter,
				Esc,
				Space,
				Plus,
				Minus,
				Period,
				Comma,
				Num_0,
				Num_1,
				Num_2,
				Num_3,
				Num_4,
				Num_5,
				Num_6,
				Num_7,
				Num_8,
				Num_9,
				Colon,
				SemiColon,
				Less,
				Greater,
				Equals,
				Question,
				Left_Bracket,
				Right_Bracket,
				Backslash,
				Underscore,
				Backquote,
				A,
				B,
				C,
				D,
				E,
				F,
				G,
				H,
				I,
				J,
				K,
				L,
				M,
				N,
				O,
				P,
				Q,
				R,
				S,
				T,
				U,
				V,
				W,
				X,
				Y,
				Z,
				Delete,
				NumPad_0,
				NumPad_1,
				NumPad_2,
				NumPad_3,
				NumPad_4,
				NumPad_5,
				NumPad_6,
				NumPad_7,
				NumPad_8,
				NumPad_9,
				NumPad_Period,
				NumPad_Divide,
				NumPad_Plus,
				NumPad_Minus,
				NumPad_Enter,
				NumPad_Equals,
				NumPad_Multiply,
				Up,
				Down,
				Right,
				Left,
				Insert,
				Home,
				End,
				PageUp,
				PageDown,
				F1,
				F2,
				F3,
				F4,
				F5,
				F6,
				F7,
				F8,
				F9,
				F10,
				F11,
				F12,
				NumLock,
				CapsLock,
				ScrolLock,
				Right_Shift,
				Left_Shift,
				Right_Ctrl,
				Left_Ctrl,
				Right_Alt,
				Left_Alt,
				Left_Windows,
				Right_Windows
			};

			/**
			 * @fn	static KeyState IKeyboard::getKey(Keys key);
			 *
			 * @brief	Gets a key current state.
			 *
			 * @author	Moustapha Saad
			 * @date	23/01/2015
			 *
			 * @param	key	The key.
			 *
			 * @return	KeyState.
			 */

			static KeyState getKey(Keys key);

			/**
			 * @fn	virtual void IKeyboard::update();
			 *
			 * @brief	Updates this object.
			 *
			 * @author	Moustapha Saad
			 * @date	23/01/2015
			 */

		protected:
			IKeyboard();

			/**
			 * @fn	virtual void IKeyboard::update();
			 *
			 * @brief	Updates this object.
			 *
			 * @author	Moustapha Saad
			 * @date	24/01/2015
			 */

			virtual void update();

			/** @brief	The data of the keys. */
			static std::map<Keys, KeyState> _data;
		};
		typedef std::shared_ptr<IKeyboard> IKeyboardPtr;
	}
}