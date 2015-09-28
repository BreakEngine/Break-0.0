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

		/**
		 * \brief represents a uniform block buffer
		 * \author Moustapha Saad
		 */
		class BREAK_API_EX UniformBuffer: public Infrastructure::GPUResource{
			friend class Renderer::GLManager;
			friend class Renderer::DXManager;
		protected:
			///data buffer
			Infrastructure::RAMBufferPtr _buffer;
			///unifrom block slot in the shader
			unsigned int _slot;
			///shader type that this block is in
			Shader::Type _shader;
			///update indicator
			bool needUpdate;

			///invokes create function to GPU
			virtual bool createGPUResource() override;
		public:

			///default constrcutor
			UniformBuffer();

			///size init constructor
			UniformBuffer(unsigned int size,unsigned int slot,Shader::Type shader);

			UniformBuffer(const UniformBuffer& val);

			virtual ~UniformBuffer();

			void clear();

			///binds the uniform buffer
			void use();

			///reallocates the current memory
			void reallocate(unsigned int size);

			///maps the data to range in buffer
			void map(void* data,unsigned int size, unsigned int start);

			///invokes sync with GPU
			void invokeUpdate();

			///appends buffer to uniform
			bool appendBuffer(void* data,unsigned int size);

			///returns buffer size
			unsigned int getSize();

			///sync the data with GPU
			void flush();

			///slot getter
			unsigned int getSlot();

			///sets buffer slot
			void setSlot(unsigned int val);

			///returns a data pointer
			byte* getData(unsigned int offset=0);
		};
		typedef std::shared_ptr<UniformBuffer> UniformBufferPtr;
	}
}