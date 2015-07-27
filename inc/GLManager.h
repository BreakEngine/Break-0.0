#pragma once
#include "IGXManager.h"
#include "Application.h"

namespace Break{
	namespace Renderer{
		class GLHandle;

		class GLManager:public Infrastructure::IGXManager{
		private:
			void applyFilter2D(GXWrapper::TextureFilter filter,bool mipmap,GLHandle* tex);
			int getAddressMode(GXWrapper::TextureAddressMode mode);
			int getCompareFunc(GXWrapper::CompareFunction func);
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
			virtual bool useUniformBuffer(Infrastructure::GPUResource*)override;

			//shader functions
			virtual bool createShader(Infrastructure::GPUResource* shader) override;
			virtual bool useShader(Infrastructure::GPUResource* shader) override;
			virtual bool deleteShader(Infrastructure::GPUResource* shader) override;

			//Texture Functions
			virtual bool createTexture2D(Infrastructure::GPUResource* texture,GXWrapper::Image& img) override;
			virtual bool updateTexture2D(Infrastructure::GPUResource* texture,GXWrapper::Image& img) override;
			virtual bool deleteTexture2D(Infrastructure::GPUResource* texture) override;
			virtual bool useTexture2D(Infrastructure::GPUResource* texture, unsigned int unit, GXWrapper::Shader::Type) override;

			//geometry functions
			virtual bool createGeometry(GXWrapper::Geometry* geometry) override;
			virtual bool drawGeometry(GXWrapper::Geometry*, GXWrapper::Primitive::Mode mode)override;
			virtual bool deleteGeometry(Infrastructure::GPUResource*)override;

			//sampler functions
			virtual bool createSamplerState(Infrastructure::GPUResource*)override;
			virtual bool useSamplerState(Infrastructure::GPUResource*,unsigned int slot, GXWrapper::Shader::Type)override;
			virtual bool deleteSamplerState(Infrastructure::GPUResource*)override;
			virtual bool applySamplerStateToTexture2D(Infrastructure::GPUResource* sampler, Infrastructure::GPUResource* texture)override;

		};
	}
}
