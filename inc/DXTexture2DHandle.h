#pragma once
#include "IGPUHandle.h"
#include <d3d11.h>
#include "GlobalDefinitions.h"

namespace Break{
	namespace Renderer{
		class BREAK_API_EX DXTexture2DHandle: public Infrastructure::IGPUHandle{
		public:
			ID3D11Texture2D* texture;
			ID3D11ShaderResourceView* resourceView;
			DXTexture2DHandle(){
				texture = NULL;
				resourceView = NULL;
			}
			virtual ~DXTexture2DHandle(){
				texture = NULL;
				resourceView = NULL;
			}

		};
	}
}