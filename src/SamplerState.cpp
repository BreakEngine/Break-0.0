#include "SamplerState.h"
#include <Engine.h>
#include <Services.h>

using namespace Break::GXWrapper;


SamplerState::SamplerState()
{
	filter = TextureFilter::LINEAR;
	addressU = TextureAddressMode::WRAP;
	addressV = TextureAddressMode::WRAP;
	addressW = TextureAddressMode::WRAP;
	borderColor = Color(255,255,255,255);
	compareFunction = CompareFunction::NEVER;
}

SamplerState::SamplerState(const SamplerState& val)
{
	addressU = val.addressU;
	addressV = val.addressV;
	addressW = val.addressW;
	borderColor = val.borderColor;
	compareFunction = val.compareFunction;
}
SamplerState::~SamplerState()
{
	//Break::Infrastructure::Engine::Instance->GraphicsDevice->deleteSamplerState(this);
	Renderer::GPUIns ins;
	ins.instruction = Renderer::GPU_ISA::DEL;
	ins.args.push(Renderer::GPU_ISA::SAMPLER);
	ins.args.push(_handle.get());
	Services::getGPU_VM()->execute(ins);
}

bool SamplerState::createGPUResource()
{
	return true;
}