#pragma once
#include "../Infrastructure/IGXManager.h"
namespace Renderer{
	class Test:public Break::Infrastructure::IGXManager{
	public:
		Test();
		virtual bool init();
	};
}