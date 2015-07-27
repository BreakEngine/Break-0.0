#pragma once
#include "IGPUHandle.h"
#include <d3d11.h>

namespace Break{
	namespace Renderer{
		class DXSamplerHandle: public Infrastructure::IGPUHandle{
		public:
			ID3D11SamplerState *sampler;

			DXSamplerHandle(){
				sampler = NULL;
			}
			virtual ~DXSamplerHandle(){
				sampler = NULL;
			}

		};
	}
}