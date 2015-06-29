#pragma once
#include <memory>
#include "GlobalDefinitions.h"
namespace Break{
	namespace Infrastructure{
		//class represents a chunk of bytes in ram
		class RAMBuffer{
		protected:

			//pointer to the data
			byte* _data;
			//size of the data
			unsigned int _size;
			//how many bytes filled
			unsigned int _fillStatus;
		public:
			//default constructor doing nothing
			RAMBuffer();
			//allocates the needed size
			RAMBuffer(unsigned int size);
			//Just converting to RAMBuffer from an ordinary array
			RAMBuffer(void* ptr,unsigned int size,bool deep = true);
			//copy constructor
			RAMBuffer(const RAMBuffer& val);

			virtual ~RAMBuffer();
			//reallocates memory
			virtual void reallocate(unsigned int size);
			//appends the following data if it can to stream
			virtual bool append(void* data,unsigned int size);
			//appends two RAM buffers
			virtual bool append(std::shared_ptr<RAMBuffer>);
			//overwrites a certain amount of data in ram
			virtual bool map(void* data,unsigned int size,unsigned int start);
			//cleans the data and free the memory
			void clear();
			//returns pointer to the data
			byte* getData(unsigned int offset=0);
			//returns size of the buffer
			unsigned int getSize();
			//returns used size
			unsigned int getUsedSize();
			//returns a deep copy of the buffer
			std::shared_ptr<RAMBuffer> clone();

		};
		typedef std::shared_ptr<RAMBuffer> RAMBufferPtr;
	}
}