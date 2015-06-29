#pragma once
#include <memory>
namespace Break{
	namespace Infrastructure{
		//predefine engine class
		class Engine;

		class InputDevice{
			//setting engine as a friend class
			friend class Engine;
		public:
			//constructor
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