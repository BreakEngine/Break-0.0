#pragma once
#include "Engine.h"
#include "GPU_VM.hpp"

namespace Break
{
	class Services
	{
		friend class Infrastructure::Engine;

		static Infrastructure::Engine* m_engine;
		static Infrastructure::IGXManager* m_graphics;
		static Renderer::GPU_VM* m_vm;

		static void registerEngine(Infrastructure::Engine* val)
		{
			m_engine = val;
		}

		static void registerGraphics(Infrastructure::IGXManager* val)
		{
			m_graphics = val;
		}

		static void registerVM(Renderer::GPU_VM* val)
		{
			m_vm = val;
		}
	public:
		static Infrastructure::Engine*
		getEngine()
		{
			return m_engine;
		}

		static Infrastructure::IGXManager*
		getGraphicsManager()
		{
			return m_graphics;
		}

		static Renderer::GPU_VM*
		getGPU_VM()
		{
			return m_vm;
		}
	};
}