#pragma once

#include "GlobalDefinitions.h"
#include "RAMBuffer.h"
#include "GPUResource.h"
#include "Shader.h"
#include <memory>
#include <string>

namespace Break{
	namespace Renderer{
		class GLManager;
		class DXManager;
	}
	namespace GXWrapper{
		class UniformBuffer: public Infrastructure::GPUResource{
			friend class Renderer::GLManager;
			friend class Renderer::DXManager;
		protected:
			Infrastructure::RAMBufferPtr _buffer;
			unsigned int _slot;
			Shader::Type _shader;
			virtual bool createGPUResource() override;
		public:
			UniformBuffer();

			UniformBuffer(unsigned int size,unsigned int slot,Shader::Type shader);

			UniformBuffer(const UniformBuffer& val);

			virtual ~UniformBuffer();

			void clear();

			void use() override;

			void reallocate(unsigned int size);

			void map(void* data,unsigned int size, unsigned int start);

			bool appendBuffer(void* data,unsigned int size);

			unsigned int getSize();

			void flush();

			unsigned int getSlot();

			void setSlot(unsigned int val);

			Infrastructure::byte* getData(unsigned int offset=0);
		};
		typedef std::shared_ptr<UniformBuffer> UniformBufferPtr;
	}
}