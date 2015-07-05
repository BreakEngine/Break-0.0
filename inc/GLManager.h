#pragma once
#include "IGXManager.h"
#include "Application.h"

namespace Break{
	namespace Renderer{
		class GLManager:public Infrastructure::IGXManager{
		private:
		public:
			GLManager();
			virtual ~GLManager();

			//inits graphics manager
			virtual bool init(Infrastructure::ApplicationPtr app) override;
			//start window loop
			virtual void start() override;
			//clears all the buffers
			virtual void clearBuffer() override;
			//swaps the buffer
			virtual void swapBuffer() override;
			//sets cursor position to specific point
			virtual void setCursorPostion(glm::uvec2 val) override;

			//buffers functions
			virtual bool createVertexBuffer(Infrastructure::GPUResource* buffer) override;
			virtual bool createIndexBuffer(Infrastructure::GPUResource* buffer) override;
			virtual bool updateVertexBuffer(Infrastructure::GPUResource* buffer, unsigned int offset, unsigned int size) override;
			virtual bool updateIndexBuffer(Infrastructure::GPUResource* buffer, uint offset, uint size) override;
			virtual bool deleteBuffer(Infrastructure::GPUResource*) override;
			virtual bool useIndexBuffer(Infrastructure::GPUResource*) override;
			virtual bool useVertexBuffer(Infrastructure::GPUResource*)override;
			virtual bool createUniformBuffer(Infrastructure::GPUResource* buffer)override;
			virtual bool updateUniformBuffer(Infrastructure::GPUResource*,unsigned int,unsigned int)override;
			virtual bool useUniformBuffer(Infrastructure::GPUResource*);

			//shader functions
			virtual bool createShader(Infrastructure::GPUResource* shader) override;
			virtual bool useShader(Infrastructure::GPUResource* shader) override;
			virtual bool deleteShader(Infrastructure::GPUResource* shader) override;
		};
	}
}
