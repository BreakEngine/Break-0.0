#pragma once
#include "IGPUHandle.h"
#include <d3d11.h>
#include "GlobalDefinitions.h"

namespace Break{
	namespace Renderer{
		class BREAK_API_EX DXSamplerHandle: public Infrastructure::IGPUHandle{
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