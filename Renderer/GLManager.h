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
			bool init(Infrastructure::ApplicationPtr app) override;
			//start window loop
			void start() override;
			//clears all the buffers
			void clearBuffer() override;
			//swaps the buffer
			void swapBuffer() override;
			//sets cursor position to specific point
			void setCursorPostion(glm::uvec2 val) override;

			//buffers functions
			bool createVertexBuffer(Infrastructure::GPUResource* buffer) override;
			bool createIndexBuffer(Infrastructure::GPUResource* buffer) override;
			bool updateVertexBuffer(Infrastructure::GPUResource* buffer, unsigned int offset, unsigned int size) override;
			bool updateIndexBuffer(Infrastructure::GPUResource* buffer, uint offset, uint size) override;
			bool deleteBuffer(Infrastructure::GPUResource*) override;
		};
	}
}
