#pragma once
#include <memory>
#include "GlobalDefinitions.h"
namespace Break{
	namespace Infrastructure{
		//class represents a chunk of bytes in ram
		class BREAK_API_EX RAMBuffer{
		protected:

			///pointer to the data
			byte* _data;
			///size of the data
			u32 _size;
			///how many bytes filled
			u32 _fillStatus;
			///boolean to indicate if this class should delete the allocated block
			bool _shouldDelete;
		public:
			///default constructor doing nothing
			RAMBuffer();

			/**
			 * \brief size init constructor
			 * \param size size of the buffer
			 * \author Moustapha Saad
			 */
			RAMBuffer(u32 size);

			///copy constructor
			RAMBuffer(const RAMBuffer& val);

			///virtual destructor
			virtual ~RAMBuffer();

			///reallocates memory
			virtual void reallocate(u32 size);

			/**
			 * \brief appends data to buffer
			 * \param data pointer to data to be appended
			 * \param size size of the data
			 * \return true if appended successfully false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool append(void* data,u32 size);

			///appends two RAM buffers
			virtual bool append(RAMBuffer*);

			/**
			 * \brief overwrites a certain amount of data in ram
			 * \param data pointer to data in memory
			 * \param size size of the data
			 * \param start offset inside the buffer
			 * \return true in case of success false otherwise
			 */
			virtual bool map(void* data,u32 size,u32 start);

			///cleans the data and free the memory
			void clear();

			///returns pointer to the data
			byte* getData(u32 offset=0);

			///returns size of the buffer
			u32 getSize();

			///returns used size
			u32 getUsedSize();


			///deletes the current buffer
			void deleteBuffer();

			/*
			 * \brief shallow copy buffer from meory
			 * \param ptr pointer to buffer in memory
			 * \param size size of the buffer in bytes
			 */
			void copyHandle(void* ptr,u32 size);

			/*
			 * \brief deep copy buffer from meory
			 * \param ptr pointer to buffer in memory
			 * \param size size of the buffer in bytes
			 */
			void copyBuffer(void* ptr,u32 size);

			///returns a deep copy of the buffer
			std::shared_ptr<RAMBuffer> clone();

		};
		typedef std::shared_ptr<RAMBuffer> RAMBufferPtr;
	}
}