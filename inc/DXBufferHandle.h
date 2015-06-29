#pragma once

#include "IGPUHandle.h"
#include <d3d11.h>

namespace Break{
	namespace Renderer{
		class DXBufferHandle:public Infrastructure::IGPUHandle{
		public:
			ID3D11Buffer* DXBuffer;

			DXBufferHandle(){
				DXBuffer = NULL;
			}

			virtual ~DXBufferHandle(){
				DXBuffer = NULL;
			}
		};
	}
}