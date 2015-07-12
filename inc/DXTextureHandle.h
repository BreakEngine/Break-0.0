#include "IGPUHandle.h"
#include <d3d11.h>
namespace Break
{
	namespace Infrastructure
	{
		class DXTextureHandle : public IGPUHandle
		{
		public:
			ID3D11Texture2D* _textureHandle;
			DXTextureHandle(){_textureHandle = 0;}
			~DXTextureHandle(){}
		};

	}
}