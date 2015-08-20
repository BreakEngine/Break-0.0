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
	namespace Renderer{
		class GLManager;
		class DXManager;
	};
	namespace Infrastructure{
		/**
		 * supportted apis by the engine
		 */
		enum class API{ OPENGL, DIRECTX };

		/**
		 * Main class of the whole engine
		 */
		class Engine{
			friend class Renderer::GLManager;
			friend class Renderer::DXManager;
		public:
			~Engine();

			/**
			 * \brief setups the engine with the needed objects to run
			 *
			 * \param app shared pointer to an instance of an application
			 * \param api choosen api to run
			 * \param renderer shared pointer to an instance of the used renderer (OPTIONAL)
			 *
			 * \author Moustapha Saad
			 */
			void setup(ApplicationPtr app, API api, IRendererPtr renderer = IRendererPtr(new IRenderer()));

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
			 * \function void shutdown()
			 *
			 * \brief terminates the whole engine
			 *
			 * \author Moustapha Saad
			 */
			void shutdown();

			IRenderer* getRenderer();
			/*!
			 * \function API getAPI()
			 *
			 * \brief returns the used api
			 *
			 * \author Moustapha Saad
			 */
			API getAPI();

			/**
			 * \brief returns a 2D orthogonal matrix of the current render target
			 * \return glm::mat4
			 * \author Moustapha Saad
			 */
			glm::mat4 get2DOrthogonal();
			
			/*!
			 * \Property Instance 
			 *
			 * \brief a read-only property of the engine class for implementing the singleton pattern
			 *
			 * \author Moustapha Saad
			 */
			static Property<std::shared_ptr<Engine>,Engine,Permission::READ> Instance;

			/**
			 * \brief read-only property of graphics device
			 * \return std::shared_ptr<IGXManager>
			 * \author Moustapha Saad
			 *
			 */
			Property<IGXManagerPtr,Engine,Permission::READ> GraphicsDevice;

			/**
			 * \brief read-only property of running application
			 * \return std::shared_ptr<Application>
			 * \author Moustapha Saad
			 *
			 */
			Property<ApplicationPtr, Engine, Permission::READ> Application;
		private:
			/**
			 * \brief cleans the engine before destruction
			 * \author Moustapha Saad
			 */
			void cleanUp();
			/*!
			 * \function get()
			 *
			 * \brief gets an instance of the engine class
			 *
			 * \author Moustapha Saad
			 */

			std::shared_ptr<Engine> get();
			void set(std::shared_ptr<Engine>);


			/**
			 * \brief initializes the audio mixer
			 * \author Mohammed Shaalan
			 */
			void initAudio();
			
			/*!
			 * \function IGXManagerPtr getGraphicsDevice()
			 *
			 * \brief returns pointer to the graphics device used
			 *
			 * \author Moustapha Saad
			 */
			IGXManagerPtr getGraphicsDevice();

			/*!
			 * \function ApplicationPtr getApplication()
			 *
			 * \brief returns a copy of the running application
			 *
			 * \author Moustapha Saad
			 */
			ApplicationPtr getApplication();

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
			void update(TimeStep);

			/*!
			 * \function render()
			 *
			 * \brief manages the render segmant of the engine
			 *
			 * \author Moustapha Saad
			 */
			void render();

			///instance variable that stores the only instance of the engine class
			static std::shared_ptr<Engine> _instance;

			///boolean value to indicate whether the engine thread will be joinable or not
			bool _joinable;

			///the main thread that the engine will run in
			std::thread* _mainThread;

			///boolean to indicate the destruction process of the engine to stop all the loops
			bool _cleaningUp;

			///boolean to indicate the if the engine should shutdown
			bool _shutdown;

			///the chosen API that will the application run
			API _api;

			///pointer to the used renderer class that'll be used in engine
			IRendererPtr _renderer;

			///pointer to the used graphics manager
			IGXManagerPtr _graphicsManager;

			///vector of input devices that the engine will hold
			std::vector<InputDevicePtr> _inputDevices;

			///Application
			ApplicationPtr _application;

			///indicates the init process has finished
			bool _initFinished;

			///orthographics projection based on display info
			glm::mat4 _2DOrthographic;

			/**
			 * private default constructor of the engine
			 */
			Engine();
		};
		///type alias for Engine shared_ptr
		typedef std::shared_ptr<Engine> EnginePtr;
	}
}