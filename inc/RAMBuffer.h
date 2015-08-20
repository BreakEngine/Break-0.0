#pragma once
#include <memory>
#include "GlobalDefinitions.h"
namespace Break{
	namespace Infrastructure{
		//class represents a chunk of bytes in ram
		class RAMBuffer{
		protected:

			///pointer to the data
			byte* _data;
			///size of the data
			unsigned int _size;
			///how many bytes filled
			unsigned int _fillStatus;
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
			RAMBuffer(unsigned int size);

			/**
			 * \brief existing data init constructor
			 * \param ptr pointer to existing data
			 * \param size size of the buffer
			 * \param deep indicates whether deep copy or shallow (OPTIONAL) default true
			 */
			RAMBuffer(void* ptr,unsigned int size,bool deep = true);

			///copy constructor
			RAMBuffer(const RAMBuffer& val);

			///virtual destructor
			virtual ~RAMBuffer();

			///reallocates memory
			virtual void reallocate(unsigned int size);

			/**
			 * \brief appends data to buffer
			 * \param data pointer to data to be appended
			 * \param size size of the data
			 * \return true if appended successfully false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool append(void* data,unsigned int size);

			///appends two RAM buffers
			virtual bool append(std::shared_ptr<RAMBuffer>);

			/**
			 * \brief overwrites a certain amount of data in ram
			 * \param data pointer to data in memory
			 * \param size size of the data
			 * \param start offset inside the buffer
			 * \return true in case of success false otherwise
			 */
			virtual bool map(void* data,unsigned int size,unsigned int start);

			///cleans the data and free the memory
			void clear();

			///returns pointer to the data
			byte* getData(unsigned int offset=0);

			///returns size of the buffer
			unsigned int getSize();

			///returns used size
			unsigned int getUsedSize();

			///transforms the current buffer to a handle to existing block of memory
			void handleToExistingBuffer(void* data,unsigned int size,bool deleteOld=true);

			///deletes the current buffer
			void deleteBuffer();

			///returns a deep copy of the buffer
			std::shared_ptr<RAMBuffer> clone();

		};
		typedef std::shared_ptr<RAMBuffer> RAMBufferPtr;
	}
}