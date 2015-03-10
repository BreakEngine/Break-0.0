#pragma once
#include<memory>
#include<thread>
#include<vector>
#include "Property.h"
#include "IRenderer.h"
#include "IGXManager.h"
#include "InputDevice.h"
#include "Application.h"
namespace Break{
	namespace Infrastructure{
		//API for choosing API that'll be used
		enum API{ OPENGL, DIRECTX, NONE };

		//main class of the engine that manages everything 
		class Engine{
		public:
			//default destructor of the engine class
			~Engine();

			/*!
			 * \function setup(API)
			 *
			 * \brief setups the engine for running
			 *
			 * \author Moustapha Saad
			 *  
			 */
			void setup(ApplicationPtr app,API,IRendererPtr r =IRendererPtr(new IRenderer()));
			/*!
			 * \function start()
			 *
			 * \brief starts the engine
			 *
			 * \author Moustapha Saad
			 */
			void start();
			/*!
			 * \function join(bool)
			 *
			 * \brief determines if the engine thread will be joined or not
			 *
			 * \author Moustapha Saad
			 */
			void join(bool val);
			
			/*!
			 * \Property Instance 
			 *
			 * \brief a read-only property of the engine class for implementing the singleton pattern
			 *
			 * \author Moustapha Saad
			 */
			static Property<std::shared_ptr<Engine>,Engine,Permission::READ> Instance;

			//property of graphics device 
			Property<IGXManagerPtr,Engine,Permission::READ> GraphicsDevice;
		private:
			/*!
			 * \function get()
			 *
			 * \brief gets an instance of the engine class
			 *
			 * \author Moustapha Saad
			 */
			std::shared_ptr<Engine> get();
			void set(std::shared_ptr<Engine>);

			
			/*!
			 * \function IGXManagerPtr getGraphicsDevice()
			 *
			 * \brief returns pointer to the graphics device used
			 *
			 * \author Moustapha Saad
			 */
			IGXManagerPtr getGraphicsDevice();

			/*!
			 * \function init()
			 *
			 * \brief initializes the engine
			 *
			 * \author Moustapha Saad
			 */
			bool init();
			/*!
			 * \function gameloop()
			 *
			 * \brief manages the gameloop of the engine
			 *
			 * \author Moustapha Saad
			 */
			void gameloop();
			/*!
			 * \function input()
			 *
			 * \brief manages the input segmant of the engine
			 *
			 * \author Moustapha Saad
			 */
			void input();
			/*!
			 * \function update()
			 *
			 * \brief manages the update segmant of the engine
			 *
			 * \author Moustapha Saad
			 */
			void update();
			/*!
			 * \function render()
			 *
			 * \brief manages the render segmant of the engine
			 *
			 * \author Moustapha Saad
			 */
			void render();

			//instance variable that stores the only instance of the engine class
			static std::shared_ptr<Engine> _instance;

			//boolean value to indicate whether the engine thread will be joinable or not
			bool _joinable;

			//the main thread that the engine will run in
			std::thread* _mainThread;

			//boolean to indicate the destruction process of the engine to stop all the loops
			bool _cleaningUp;

			//the chosen API that will the application run
			API _api;

			//pointer to the used renderer class that'll be used in engine
			IRendererPtr _renderer;

			//pointer to the used graphics manager
			IGXManagerPtr _graphicsManager;

			//vector of input devices that the engine will hold
			std::vector<InputDevicePtr> _inputDevices;

			//Application
			ApplicationPtr _application;

			//constructor of the engine
			Engine();
		};
		typedef std::shared_ptr<Engine> EnginePtr;
	}
}