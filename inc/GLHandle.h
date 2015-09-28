#pragma once
#include "IGPUHandle.h"
#include <GL/glew.h>
#include "GlobalDefinitions.h"

namespace Break{
	namespace Renderer{
		class BREAK_API_EX GLHandle:public Infrastructure::IGPUHandle{
		public:
			//id to that resource
			GLuint ID;
		};
	}
}