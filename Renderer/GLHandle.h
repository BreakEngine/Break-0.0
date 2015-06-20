#pragma once
#include "../Infrastructure/IGPUHandle.h"
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