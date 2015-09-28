#pragma once

#include <memory>
#include "GlobalDefinitions.h"

namespace Break{
	namespace Infrastructure{
		/*!
		 * this class is meant to resemble a handle to a gpu resource
		 */
		class BREAK_API_EX  IGPUHandle{
		public:
			IGPUHandle(){

			}

			virtual ~IGPUHandle(){

			}
		};
		typedef std::shared_ptr<IGPUHandle> IGPUHandlePtr;
	}
}