#pragma once

#include <memory>

namespace Break{
	namespace Infrastructure{
		/*!
		 * this class is meant to resemble a handle to a gpu resource
		 */
		class IGPUHandle{
		public:
			IGPUHandle(){

			}

			virtual ~IGPUHandle(){

			}
		};
		typedef std::shared_ptr<IGPUHandle> IGPUHandlePtr;
	}
}