#pragma once

#include "Buffer.h"
#include "ISet.h"
#include "RAMBuffer.h"

namespace Break{
	namespace GXWrapper{
		/*!
		 * an abstraction of the index buffer
		 */
		class IndexBuffer : public Buffer<ISet>{
		public:
			IndexBuffer(const IndexBuffer& val);

			IndexBuffer(Buffer::Type);

			IndexBuffer(ISet*,Buffer::Type = Buffer::STATIC);

			IndexBuffer(Infrastructure::RAMBufferPtr,Buffer::Type);

			IndexBuffer(unsigned int size = Buffer::STATIC_OPTIMAL_SIZE,Type type = Buffer::STATIC);

			virtual ~IndexBuffer();

			virtual bool append(ISet*) override;

			virtual void use();

		protected:
			
			virtual bool createGPUResource() override;

			virtual bool updateBuffer(unsigned int offset, unsigned int size) override;
		};
	}
}