#pragma once
#include "DXManager.h"

namespace Break{
	namespace Renderer{

		class DX_Windw
		{
		public:
			DX_Windw(void);
			~DX_Windw(void);

			bool Initialize(int&, int&);
			void Shutdown();

			HWND gethandle();

			static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
		private:
			const bool FULL_SCREEN = false;
			LPCSTR m_applicationName;
			HINSTANCE m_hinstance;
			HWND m_hwnd;

		};
	}
}
