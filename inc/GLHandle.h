#pragma once
#include "IGPUHandle.h"
#include <GL/glew.h>

namespace Break{
	namespace Renderer{
		class GLHandle:public Infrastructure::IGPUHandle{
		public:
			//id to that resource
			GLuint ID;
		};
	}
}