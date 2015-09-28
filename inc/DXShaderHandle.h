#pragma once
#include "IGPUHandle.h"
#include <d3d11.h>
#include "GlobalDefinitions.h"

namespace Break{
	namespace Renderer{
		class BREAK_API_EX DXShaderHandle: public Infrastructure::IGPUHandle{
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