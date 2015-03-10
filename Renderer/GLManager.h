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

			bool init(Infrastructure::ApplicationPtr app);
			void start();
			void clearBuffer();
			void swapBuffer();
			void setCursorPostion(glm::uvec2 val);
		};
	}
}