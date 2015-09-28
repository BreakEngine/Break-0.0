#pragma once

#include "Buffer.h"
#include "VertexSet.h"
#include "RAMBuffer.h"
#include "MemoryLayout.h"

namespace Break{

	namespace GXWrapper{

		/*!
		 * \brief This class is meant to be as an abstract representation of the vertex buffer
		 * \author Moustapha Saad
		 */
		class BREAK_API_EX VertexBuffer : public Buffer<ISet>{
		public:

			///copy constructor
			VertexBuffer(const VertexBuffer& val);

			///constructor for initializing an empty buffer based on type
			VertexBuffer(Buffer::Type,MemoryLayout layout);

			///constructor for initializing from a vertex set, the managed way
			VertexBuffer(ISet*,MemoryLayout layout,Buffer::Type = Buffer::STATIC);

			///constructor for initializing from a RAMBuffer
			VertexBuffer(Infrastructure::RAMBufferPtr,MemoryLayout layout,Buffer::Type);

			virtual ~VertexBuffer();

			///appends set to the buffer
			virtual bool append(ISet* set) override;

			///binds buffer to graphics context
			virtual void use();

			///layout setter
			void setLayout(MemoryLayout& layout);
			///layout getter
			MemoryLayout getLayout();

		protected:

			virtual bool createGPUResource() override;

			virtual bool updateBuffer(unsigned int offset, unsigned int size) override;

			MemoryLayout _layout;

		};

	}

}