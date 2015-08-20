#pragma once
#include "Pixels.h"
#include <memory>
#include "GPUResource.h"

namespace Break
{
	namespace GXWrapper
	{
		///texture address modes
		enum class TextureAddressMode
		{
			WRAP=0, CLAMP, MIRROR, BORDER
		};

		///texture filters to be applied to sampler
		enum class TextureFilter
		{
			LINEAR=0, POINT, ANISOTROPIC, LINEAR_MIP_POINT, POINT_MIP_LINEAR,
			MIN_LINEAR_MAG_POINT_MIP_LINEAR,MIN_LINEAR_MAG_POINT_MIP_POINT,
			MIN_POINT_MAG_LINEAR_MIP_LINEAR,MIN_POINT_MAG_LINEAR_MIP_POINT
		};

		///texture compare functions
		enum class CompareFunction
		{
			ALWAYS=0, NEVER, LESS, LESS_EQUAL, EQUAL, GREATER_EQUAL, GREATER,
			NOT_EQUAL
		};

		///represents a sampler unit
		class SamplerState: public Infrastructure::GPUResource
		{
		protected:
			///invokes a GPU create function
			bool createGPUResource() override;
		public:
			///U,V,W address modes
			TextureAddressMode addressU, addressV, addressW;
			///border color of sampler
			Color borderColor;
			///texture filter
			TextureFilter filter;
			///texture compare function
			CompareFunction compareFunction;

			SamplerState();

			SamplerState(const SamplerState& val);

			virtual ~SamplerState();
		};
		typedef std::shared_ptr<SamplerState> SamplerStatePtr;
	}
}