#pragma once
#include "IDisplay.h"
#include "TimeStep.h"
#include <memory>
namespace Break{
	namespace Renderer{
		class GLManager;
		class DXManager;
		class DX_Windw;
		class DX;
	}
	namespace Infrastructure{
		
		class Application{
			friend class Renderer::GLManager;
			friend class Renderer::DXManager;
		protected:
			IDisplayPtr _display;
		public:
			Application();
			virtual ~Application();

			IDisplayPtr getDisplay();
			//setup function called once
			virtual void init();
			//setup scene function called once
			virtual void setupScene();
			//load Resources function called once
			virtual void loadResources();

			/**
			 * @fn	virtual void Application::cleanUp();
			 *
			 * @brief	Clean up resources used in this application.
			 *
			 * @author	Moustapha Saad
			 * @date	05/02/2015
			 */

			virtual void cleanUp();

			//functions that will be called every frame
			//input function
			virtual void input();
			//update it will take the timestep later
			virtual void update(TimeStep time);
			//render function
			virtual void render();

		};
		typedef std::shared_ptr<Application> ApplicationPtr;
	}
}
