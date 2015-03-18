#pragma once
#include "DXManager.h"

namespace Break{
	namespace Renderer{

		class DX
		{
		public:
			DX(void);
			~DX(void);

			bool Initialize(int, int, bool, HWND, bool, float, float);
			void Shutdown();

			void Begin(float, float, float, float);
			void End();

			//interface to handle all buffer creation functions..
			ID3D11Device* GetDevice();
			//interface to controll GPU to draw..
			ID3D11DeviceContext* GetDeviceContext();


			void GetVideoCardInfo(char*, int&);

		private:
			//informations about gpu..
			bool m_vsync_enabled;
			int m_videoCardMemory;
			char m_videoCardDescription[128];


			IDXGISwapChain* m_swapChain; //controll frame buffer ..

			ID3D11Device* m_device;
			ID3D11DeviceContext* m_deviceContext;

			ID3D11RenderTargetView* m_renderTargetView; //Get the properties of a render target view.

			ID3D11Texture2D* m_depthStencilBuffer; //handle probs of texture Resorces..

			ID3D11DepthStencilState* m_depthStencilState; //control depth buffer..

			ID3D11DepthStencilView* m_depthStencilView; //just getter Get the depth-stencil view.

			ID3D11RasterizerState* m_rasterState; //Gets the description for rasterizer state that you used to create the rasterizer-state object.
		};

	}
}

