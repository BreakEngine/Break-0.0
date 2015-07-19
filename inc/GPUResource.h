#pragma once

#include "IGPUHandle.h"
#include <memory>

namespace Break{
	namespace Renderer{
		class GLManager;
		class DXManager;
	}
	namespace Infrastructure{
		//this class resembles a gpu resource
		class GPUResource{
			friend class Renderer::GLManager;
			friend class Renderer::DXManager;
		protected:
			//pointer to the handle
			IGPUHandlePtr _handle;

			virtual bool createGPUResource()=0;

		public:

			GPUResource(){
				_handle = nullptr;
			}

			GPUResource(const GPUResource& val){
				_handle = val._handle;
			}

			virtual ~GPUResource(){
				_handle = nullptr;
			}


		};
		typedef std::shared_ptr<GPUResource> GPUResourcePtr;
	}
}