#pragma once

#include "Buffer.h"
#include "ISet.h"
#include "RAMBuffer.h"
#include "GlobalDefinitions.h"

namespace Break{
	namespace GXWrapper{
		/*!
		 * \brief  an abstraction of the index buffer
		 * \author Moustapha Saad
		 */
		class BREAK_API_EX IndexBuffer : public Buffer<ISet>{
		public:

			///copy constructor
			IndexBuffer(const IndexBuffer& val);

			/**
			 * \brief type init constructor
			 * \param type type of the buffer
			 * \author Moustapha Saad
			 */
			IndexBuffer(Buffer::Type type);

			/**
			 * \brief set init constructor
			 * \param set of data to initialize with
			 * \param type type of the data
			 * \author Moustapha Saad
			 */
			IndexBuffer(ISet* set,Buffer::Type type= Buffer::STATIC);

			/**
			 * \brief ram initializer constructor
			 * \param ramBuffer data buffer to be initialzed to
			 * \param type type of the buffer
			 * \author Moustapha Saad
			 */
			IndexBuffer(Infrastructure::RAMBufferPtr,Buffer::Type);

			/**
			 * \brief size initializer constructor
			 * \param size size of the buffer
			 * \param type type of the buffer
			 * \author Moustapha Saad
			 */
			IndexBuffer(unsigned int size = Buffer::STATIC_OPTIMAL_SIZE,Type type = Buffer::STATIC);

			///virtual default destructor
			virtual ~IndexBuffer();

			/**
			 * \brief appends set of data to buffer
			 * \param set set of the data to be appended
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool append(ISet* set) override;

			/**
			 * \brief binds the index buffer
			 * \author Moustapha Saad
			 */
			virtual void use();

		protected:
			/**
			 * \brief creates the GPU index buffer
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool createGPUResource() override;

			/**
			 * \brief updates the index buffer
			 * \param offset offset inside buffer to start with
			 * \param size size of the buffer to be updated
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool updateBuffer(unsigned int offset, unsigned int size) override;
		};
	}
}