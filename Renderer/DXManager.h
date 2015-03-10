#pragma once
#include "../Infrastructure/IGXManager.h"
#include "../Infrastructure/Application.h"
namespace Break{
	namespace Renderer{
		class DXManager:public Infrastructure::IGXManager{
		private:
		public:
			DXManager();
			~DXManager();

			bool init(Infrastructure::ApplicationPtr app);
			void start();
			void clearBuffer();
			void swapBuffer();
			void setCursorPostion(glm::uvec2 val);
		};
	}
}