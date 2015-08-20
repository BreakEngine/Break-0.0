#pragma once

#include "RAMBuffer.h"
#include "GlobalDefinitions.h"
#include "GPUResource.h"

namespace Break{

	namespace GXWrapper{
		/*!
		 * \brief This class works as a parent for any kind of buffer it contains the needed data to work with buffers
		 *		  buffers in turn work only with sets of data which can be vertex or index set
		 * \author Moustapha Saad
		 */
		template<class T>
		class Buffer : public Infrastructure::GPUResource{
		public:
			/**
			 * \brief types of buffer
			 */
			enum Type
			{
				DYNAMIC = 0,STATIC = 1
			};

		protected:

			///optimal sizes of the buffer
			static const unsigned int STATIC_OPTIMAL_SIZE,DYNAMIC_OPTIMAL_SIZE;

			///corresponding ram buffer
			Infrastructure::RAMBufferPtr _buffer;

			///changed flag
			bool _changed;

			///Buffer Type
			Type _type;

			/*!
			 *
			 * \brief creates a buffer in the gpu that resembles this buffer
			 *
			 * \author Moustapha Saad
			 */
			virtual bool createGPUResource()=0;

			/*!
			 *
			 * \brief signals an update to the engine depends on the buffer type
			 *
			 * \param offset start address to update
			 * \param size size of memory to update
			 * \author Moustapha Saad
			 */
			virtual bool updateBuffer(unsigned int offset, unsigned int size)=0;

		public:


		
			///default constructor
			Buffer(){
				_changed = false;
				_buffer = nullptr;
			}

			/**
			 * \brief constructor which also allocates buffer memory
			 * \param size size of the buffer
			 * \author Moustapha Saad
			 */
			Buffer(unsigned int size){
				_buffer = Infrastructure::RAMBufferPtr(new Infrastructure::RAMBuffer(size));
				_changed = true;
			}

			///copy constructor
			Buffer(const Buffer& val):GPUResource(val){
				_buffer = val._buffer;
				_changed = val._changed;
			}

			///virtual default destructor
			virtual ~Buffer(){
				if(_buffer)
					_buffer = nullptr;
				
			}

			/**
			 * \brief appends set of data to the buffer if there's a space
			 * \param set data set to be appended
			 * \return true if successfully appended false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool append(T* set) = 0;


			/**
			 * \brief clears the current memory buffer
			 * \author Moustapha Saad
			 */
			void clear(){
				_buffer->clear();
				_changed = true;
			}

			/**
			 * \brief reallocates the current memory buffer
			 * \param size new size of the buffer
			 * \author Moustapha Saad
			 */
			void reallocate(unsigned int size){
				_buffer->reallocate(size);
				updateBuffer(0,_buffer->getSize());
				_changed = true;
			}

			/**
			 * \brief maps data to buffer range
			 * \param data pointer to the data to be mapped
			 * \param size size of the data memory
			 * \param start start position in buffer memory
			 * \param flush if true then it will also apply mapping to GPU side buffer immediately (OPTIONAL- default = true)
			 * \author Moustapha Saad
			 */
			void map(void* data,unsigned int size, unsigned int start, bool flush = true){
				_changed = true;
				if(_buffer->map(data,size,start)){
					//Engine::Instance->GraphicsDevice->updateVertexBuffer(this,start,size);
					if(flush)
						updateBuffer(start,size);
				}
			}

			/**
			 * \brief appends raw memory to the current buffer
			 * \param data pointer to data in memory
			 * \param size size of the data
			 * \return true if append successfully, otherwise false
			 * \author Moustapha Saad
			 *
			 */
			bool appendBuffer(void* data,unsigned int size){
				_changed = true;
				return _buffer->append(data,size);
			}

			/**
			 * \brief creates a buffer that's just a handle to other memory that's managed by user
			 * \param data pointer to data in memory
			 * \param size size of the data
			 * \author Moustapha Saad
			 */
			void fromHandle(void* data,unsigned int size)
			{
				_buffer->handleToExistingBuffer(data,size);
			}

			/**
			 * \brief returns the size of the buffer
			 * \return size of the buffer
			 * \author Moustapha Saad
			 */
			unsigned int getSize(){
				return _buffer->getSize();
			}

			/**
			 * \brief used size getter
			 * \return size of the used memory in the buffer
			 * \author Moustapha Saad
			 */
			unsigned int getUsedSize(){
				return _buffer->getUsedSize();
			}

			/**
			 * \brief performs a sync with the GPU buffer if there's a changes happend
			 * \author Moustapha Saad
			 *
			 */
			void flush(){
				if(!_handle)
					createGPUResource();
				else
					updateBuffer(0,_buffer->getSize());
			}

			/**
			 * \brief buffer type getter
			 * \return Type
			 * \author Moustapha Saad
			 */
			Type getType(){
				return _type;
			}

			/**
			 * \brief gets the buffer data pointer
			 * \param offset offset inside the buffer
			 * \return byte pointer to the data in memory
			 * \author Moustapha Saad
			 */
			Infrastructure::byte* getData(unsigned int offset = 0){
				return _buffer->getData(offset);
			}

		};


		///Dynamic buffer optimal size = 8MB
		template<class T>
		const unsigned int Buffer<T>::DYNAMIC_OPTIMAL_SIZE = 8*1024*1024;
		///Static buffer optimal size = 40MB
		template<class T>
		const unsigned int Buffer<T>::STATIC_OPTIMAL_SIZE = 40*1024*1024;

	}

}