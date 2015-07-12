#include "gl/glew.h"
#include "IGPUHandle.h"
namespace Break
{
	namespace Infrastructure
	{
		class GLTextureHandle
		{
		public:
			GLuint _textureHandle;
			GLTextureHandle(){}
			~GLTextureHandle(){}
		};

	}
}