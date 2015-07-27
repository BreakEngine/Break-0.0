#pragma once
#include "Pixels.h"
#include <memory>
#include "GPUResource.h"

namespace Break
{
	namespace GXWrapper
	{
		enum class TextureAddressMode
		{
			WRAP=0, CLAMP, MIRROR, BORDER
		};

		enum class TextureFilter
		{
			LINEAR=0, POINT, ANISOTROPIC, LINEAR_MIP_POINT, POINT_MIP_LINEAR,
			MIN_LINEAR_MAG_POINT_MIP_LINEAR,MIN_LINEAR_MAG_POINT_MIP_POINT,
			MIN_POINT_MAG_LINEAR_MIP_LINEAR,MIN_POINT_MAG_LINEAR_MIP_POINT
		};

		enum class CompareFunction
		{
			ALWAYS=0, NEVER, LESS, LESS_EQUAL, EQUAL, GREATER_EQUAL, GREATER,
			NOT_EQUAL
		};

		class SamplerState: public Infrastructure::GPUResource
		{
		protected:
			bool createGPUResource() override;
		public:
			TextureAddressMode addressU, addressV, addressW;
			Color borderColor;
			TextureFilter filter;
			CompareFunction compareFunction;

			SamplerState();

			SamplerState(const SamplerState& val);

			virtual ~SamplerState();
		};
		typedef std::shared_ptr<SamplerState> SamplerStatePtr;
	}
}