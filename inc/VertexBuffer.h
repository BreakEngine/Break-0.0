#pragma once

#include "Buffer.h"
#include "VertexSet.h"
#include "RAMBuffer.h"

namespace Break{

	namespace GXWrapper{

		/*!
		 * This class is meant to be as an abstract representation of the vertex buffer
		 */
		class VertexBuffer : public Buffer<ISet>{

		public:

			//copy constructor
			VertexBuffer(const VertexBuffer& val);

			//constructor for initializing an empty buffer based on type
			VertexBuffer(Buffer::Type);

			//constructor for initializing from a vertex set, the managed way
			VertexBuffer(ISet*,Buffer::Type = Buffer::STATIC);

			//constructor for initializing from a RAMBuffer
			VertexBuffer(Infrastructure::RAMBufferPtr,Buffer::Type);

			//configurable size constructor
			VertexBuffer(unsigned int size = Buffer::STATIC_OPTIMAL_SIZE,Type = Buffer::STATIC);

			virtual ~VertexBuffer();

			virtual bool append(ISet* set) override;

		protected:

			virtual bool createGPUBuffer() override;

			virtual bool updateBuffer(unsigned int offset, unsigned int size) override;

		};

	}

}