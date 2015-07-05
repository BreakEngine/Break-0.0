#pragma once
#include <Windows.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include "IGXManager.h"
#include "Application.h"
#include "MemoryElement.h"

namespace Break{
	namespace Renderer{
		class DXManager:public Infrastructure::IGXManager{
		protected:
			//swap chain to control frame buffer
			IDXGISwapChain* _swapChain;
			ID3D11Device* _device;
			ID3D11DeviceContext* _deviceContext;

			//get properties of a render target view.
			ID3D11RenderTargetView* _renderTargetView;
			//handle props of texture resources
			ID3D11Texture2D* _depthStencilBuffer;
			//control depth buffer
			ID3D11DepthStencilState* _depthStencilState;
			//getter get depth-stencil view
			ID3D11DepthStencilView* _depthStencilView;
			//get description for rasterizer state that you used to create raster-state object
			ID3D11RasterizerState* _rasterState;
			//GPU Info
			bool _vsync;
			unsigned int _videoCardMemory;
			char _videoCardDescription[128];
		private:
			//setups DX
			bool initD3D(HWND hWnd, int Width, int Height, bool vsync, bool fullscreen );
			//window start
			void windowStart();
			//closes DX
			void cleanD3D();

			static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			//takes element type and returns element DX format
			DXGI_FORMAT getFormat(GXWrapper::MemoryElement& element);
		public:
			DXManager();
			~DXManager();

			bool init(Infrastructure::ApplicationPtr app);
			void start();
			void clearBuffer();
			void swapBuffer();
			void setCursorPostion(glm::uvec2 val);

			bool createVertexBuffer(Infrastructure::GPUResource* buffer) override;
			bool createIndexBuffer(Infrastructure::GPUResource* buffer) override;
			bool updateVertexBuffer(Infrastructure::GPUResource*,uint offset,uint size) override;
			bool updateIndexBuffer(Infrastructure::GPUResource* buffer, uint offset, uint size) override;
			bool deleteBuffer(Infrastructure::GPUResource* buffer) override;
			bool useVertexBuffer(Infrastructure::GPUResource* buffer) override;
			bool useIndexBuffer(Infrastructure::GPUResource* buffer) override;
			bool createUniformBuffer(Infrastructure::GPUResource* buffer) override;
			bool useUniformBuffer(Infrastructure::GPUResource* buffer) override;
			bool updateUniformBuffer(Infrastructure::GPUResource* buffer,uint offset,uint size) override;

			bool createShader(Infrastructure::GPUResource* shader) override;
			bool useShader(Infrastructure::GPUResource* shader) override;
			bool deleteShader(Infrastructure::GPUResource* shader) override;
		};
	}
}