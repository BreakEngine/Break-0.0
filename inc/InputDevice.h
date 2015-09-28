#pragma once
#include <memory>
#include "GlobalDefinitions.h"
namespace Break{
	namespace Infrastructure{
		//predefine engine class
		class Engine;

		///represents an input device
		class BREAK_API_EX InputDevice{
			friend class Engine;
		public:
			///default constructor
			InputDevice();
			//virtual destructor
			virtual ~InputDevice();


		protected:

			/*!
			 * \function virtual void update()
			 *
			 * \brief used to invoke update function of the device
			 *
			 * \author Moustapha Saad
			 */
			virtual void update();

		};
		typedef std::shared_ptr<InputDevice> InputDevicePtr;
	}
}