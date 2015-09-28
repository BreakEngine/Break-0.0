#pragma once

#include "IGPUHandle.h"
#include <memory>
#include "GlobalDefinitions.h"
namespace Break{
	namespace Renderer{
		class GLManager;
		class DXManager;
	}
	namespace Infrastructure{
		/**
		 * \brief represents a gpu resource class
		 * \author Moustapha Saad
		 */
		class BREAK_API_EX GPUResource{
			friend class Renderer::GLManager;
			friend class Renderer::DXManager;
		protected:
			///pointer to the handle
			IGPUHandlePtr _handle;

			/**
			 * \brief abstract function that invoke creation function to GPU
			 * \return true in case of success false otherwise
			 * \author Moustapha Saad
			 */
			virtual bool createGPUResource()=0;

		public:

			///defualt constructor
			GPUResource(){
				_handle = nullptr;
			}

			///copy constructor
			GPUResource(const GPUResource& val){
				_handle = val._handle;
			}

			///virtaul default destrcutor
			virtual ~GPUResource(){
				_handle = nullptr;
			}

			IGPUHandle* getHandle()
			{
				return _handle.get();
			}

			void setHandle(IGPUHandlePtr val)
			{
				_handle = val;
			}

		};
		///type alias of GPUResource shared_ptr
		typedef std::shared_ptr<GPUResource> GPUResourcePtr;
	}
}