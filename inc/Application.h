#pragma once
#include "IDisplay.h"
#include "TimeStep.h"
#include <memory>
#include "Scene.h"

namespace Break{
	namespace Renderer{
		class GLManager;
		class DXManager;
	}
	namespace Infrastructure{
		/**
		 * \brief represents the application that engine will run
		 * \author Moustapha Saad
		 */
		class Application{
			friend class Renderer::GLManager;
			friend class Renderer::DXManager;
		protected:
			/// display of this application
			IDisplayPtr display;

			/// scene that's being rendered by this application
			Graphics::Scene* scene;
			/// handle to scene's spritebatch just for easy access
			Graphics::SpriteBatch* spriteBatch;

			/*!
			 *
			 * \brief closes the Application
			 *
			 * \author Moustapha Saad
			 */
			void shutdown();
		public:
			/**
			 * \brief default constructor
			 * \author Moustapha Saad
			 */
			Application();

			/**
			 * \brief default virtual destructor
			 * \author Moustapha Saad
			 */
			virtual ~Application();

			/**
			 * \brief returns the display of this application
			 * \return std::shared_ptr<IDisplay>
			 * \author Moustapha Saad
			 */
			IDisplayPtr getDisplay();

			/**
			 * \brief initialization function called only once at start
			 * \author Moustapha Saad
			 */
			virtual void init();

			/**
			 * \brief resource loading function called only once at start
			 * \author Moustapha Saad
			 */
			virtual void loadResources();

			/**
			 * \brief setup function called only once at start
			 * \author Moustapha Saad
			 */
			virtual void setupScene();

			/**
			 *
			 * \brief	Clean up resources used in this application.
			 *
			 * \author	Moustapha Saad
			 */

			virtual void cleanUp();


			/**
			 * \brief input function called once every frame
			 * \author Moustapha Saad
			 */
			virtual void input();

			/**
			 * \brief update function called once every frame
			 * \param time time step that has info about delta time and elapsed time
			 * \author Moustapha Saad
			 */
			virtual void update(TimeStep time);

			/**
			 * \brief render function called once every frame
			 * \author Moustapha Saad
			 */
			virtual void render();

		};
		///type alias for application shared_ptr
		typedef std::shared_ptr<Application> ApplicationPtr;
	}
}
