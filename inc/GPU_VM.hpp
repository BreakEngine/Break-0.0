#pragma once
#include "GPUIns.hpp"
#include <memory>
#include "IGPUHandle.h"

namespace Break
{
	namespace Renderer
	{
		class GPU_VM
		{
			Arg pop(std::queue<Arg>& args);
		public:
			GPU_VM();
			~GPU_VM();
			Infrastructure::IGPUHandlePtr execute(GPUIns& ins);

		};
		typedef std::shared_ptr<GPU_VM> GPU_VMPtr;
	}
}