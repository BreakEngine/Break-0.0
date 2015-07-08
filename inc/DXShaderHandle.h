#pragma once
#include "IGPUHandle.h"
#include <d3d11.h>

namespace Break{
	namespace Renderer{
		class DXShaderHandle: public Infrastructure::IGPUHandle{
		public:
			ID3D11VertexShader* vertexShader;
			ID3D11PixelShader* pixelShader;
			ID3D11InputLayout* inputLayout;

			DXShaderHandle(){
				vertexShader = NULL;
				pixelShader = NULL;
				inputLayout = NULL;
			}
			virtual ~DXShaderHandle(){
				vertexShader = NULL;
				pixelShader = NULL;
				inputLayout = NULL;
			}

		};
	}
}