#pragma once
#include "IGPUHandle.h"
#include <GL/glew.h>
namespace Break{
	namespace Renderer{
		class GLShaderHandle:public Infrastructure::IGPUHandle{
		public:
			GLuint vertexShader;
			GLuint pixelShader;
			GLuint program;
		};
	}
}