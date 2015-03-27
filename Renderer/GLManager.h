#pragma once
#include "../Infrastructure/IGXManager.h"
#include "../Infrastructure/Application.h"
namespace Break{
	namespace Renderer{
		class GLManager:public Infrastructure::IGXManager{
		private:
		public:
			GLManager();
			~GLManager();

			//inits graphics manager
			bool init(Infrastructure::ApplicationPtr app);
			//start window loop
			void start();
			//clears all the buffers
			void clearBuffer();
			//swaps the buffer
			void swapBuffer();
			//sets cursor position to specific point
			void setCursorPostion(glm::uvec2 val);
		};
	}
}