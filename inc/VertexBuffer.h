#pragma once

#include "Buffer.h"
#include "VertexSet.h"
#include "RAMBuffer.h"
#include "MemoryLayout.h"

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
			VertexBuffer(Buffer::Type,MemoryLayout& layout);

			//constructor for initializing from a vertex set, the managed way
			VertexBuffer(ISet*,MemoryLayout& layout,Buffer::Type = Buffer::STATIC);

			//constructor for initializing from a RAMBuffer
			VertexBuffer(Infrastructure::RAMBufferPtr,MemoryLayout& layout,Buffer::Type);

			//configurable size constructor
			VertexBuffer(unsigned int size = Buffer::STATIC_OPTIMAL_SIZE,Type = Buffer::STATIC);

			virtual ~VertexBuffer();

			virtual bool append(ISet* set) override;

			virtual void use() override;

			void setLayout(MemoryLayout& layout);

			MemoryLayout getLayout();

		protected:

			virtual bool createGPUResource() override;

			virtual bool updateBuffer(unsigned int offset, unsigned int size) override;

			MemoryLayout _layout;

		};

	}

}