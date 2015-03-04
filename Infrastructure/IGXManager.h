#pragma once
#include<memory>
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
			virtual bool init();

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

		};
		typedef std::shared_ptr<IGXManager> IGXManagerPtr;
	}
}