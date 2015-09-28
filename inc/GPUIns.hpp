#pragma once
#include "Argument.hpp"
#include "GPU_ISA.hpp"
#include <queue>
namespace Break
{
	namespace Renderer
	{

		class GPUIns
		{
		public:
			GPU_ISA instruction;
			std::queue<Arg> args;
		};
	}
}