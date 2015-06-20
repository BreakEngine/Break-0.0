#pragma once

#include "../Infrastructure/RAMBuffer.h"
#include "../Infrastructure/GlobalDefinitions.h"
#include "../Infrastructure/GPUResource.h"

namespace Break{

	namespace GXWrapper{
		/*!
		 * This class works as a parent for any kind of buffer it contains the needed data to work with buffers
		 * buffers in turn work only with sets of data which can be vertex or index set
		 */
		template<class T>
		class Buffer : public Infrastructure::GPUResource{
		public:
			//enum of type
			enum Type
			{
				DYNAMIC = 0,STATIC = 1
			};
		protected:

			static const unsigned int STATIC_OPTIMAL_SIZE,DYNAMIC_OPTIMAL_SIZE;

			//corresponding ram buffer
			Infrastructure::RAMBufferPtr _buffer;

			//changed flag
			bool _changed;

			//Buffer Type
			Type _type;

			/*!
			 * \function virtual bool createBuffer();
			 *
			 * \brief creates a buffer in the gpu that resembles this buffer
			 *
			 * \author Moustapha Saad
			 */
			virtual bool createGPUBuffer()=0;

			/*!
			 * \function virtual bool updateBuffer(unsigned int offset, unsigned int size)
			 *
			 * \brief signals an update to the engine depends on the buffer type
			 *
			 * \author Moustapha Saad
			 */
			virtual bool updateBuffer(unsigned int offset, unsigned int size)=0;

		public:


		
			//default constructor
			Buffer(){
				_changed = false;
				_buffer = nullptr;
			}

			Buffer(unsigned int size){
				_buffer = Infrastructure::RAMBufferPtr(new RAMBuffer(size));
				_changed = true;
			}

			Buffer(const Buffer& val):GPUResource(val){
				_buffer = val._buffer;
				_changed = val._changed;
			}

			virtual ~Buffer(){
				if(_buffer)
					_buffer = nullptr;
				
			}

			virtual bool append(T* set) = 0;

			void clear(){
				_buffer->clear();
				_changed = true;
			}

			void reallocate(unsigned int size){
				_buffer->reallocate(size);
				updateBuffer(0,_buffer->getSize());
				_changed = true;
			}

			void map(void* data,unsigned int size, unsigned int start){
				_changed = true;
				if(_buffer->map(data,size,start)){
					//Engine::Instance->GraphicsDevice->updateVertexBuffer(this,start,size);
					updateBuffer(start,size);
				}
			}

			bool appendBuffer(void* data,unsigned int size){
				_changed = true;
				return _buffer->append(data,size);
			}

			unsigned int getSize(){
				return _buffer->getSize();
			}

			unsigned int getUsedSize(){
				return _buffer->getUsedSize();
			}

			void flush(){
				createGPUBuffer();
			}

			Type getType(){
				return _type;
			}

			Infrastructure::byte* getData(unsigned int offset = 0){
				return _buffer->getData(offset);
			}

		};


		//Dynamic buffer optimal size = 8MB
		template<class T>
		const unsigned int Buffer<T>::DYNAMIC_OPTIMAL_SIZE = 8*1024*1024;
		//Static buffer optimal size = 40MB
		template<class T>
		const unsigned int Buffer<T>::STATIC_OPTIMAL_SIZE = 40*1024*1024;

	}

}