#pragma once
#include "IGPUHandle.h"
#include <GL/glew.h>
#include "GlobalDefinitions.h"

namespace Break{
	namespace Renderer{
		class BREAK_API_EX GLShaderHandle:public Infrastructure::IGPUHandle{
		public:
			GLuint vertexShader;
			GLuint pixelShader;
			GLuint program;
		};
	}
}