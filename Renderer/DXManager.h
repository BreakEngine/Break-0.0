#pragma once
#include "../Infrastructure/IGXManager.h"
#include "../Infrastructure/Application.h"

namespace Break{
	namespace Renderer{
		class DXManager:public Infrastructure::IGXManager{
		private:
		public:
			DXManager();
			~DXManager();

			bool init(Infrastructure::ApplicationPtr app);
			void start();
			void clearBuffer();
			void swapBuffer();
			void setCursorPostion(glm::uvec2 val);


			//functions..
			// function prototypes
			bool InitD3D(HWND hWnd,int Width, int Height, bool vsync, bool fullscreen);    // sets up and initializes Direct3D
			void RenderFrame(void);     // renders a single frame
			int CleanD3D(void);        // closes Direct3D and releases memory

			void Begin(float color[]);
			void End();

			// the WindowProc function prototype
			static  LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);



			//informations about gpu..
			bool m_vsync_enabled;
			int m_videoCardMemory;
			char m_videoCardDescription[128];


			HWND hWnd;

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
