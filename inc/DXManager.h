#pragma once
#ifdef _WIN32
#include <Windows.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include "IGXManager.h"
#include "Application.h"
#include "MemoryElement.h"
#include "GlobalDefinitions.h"

namespace Break{
	namespace Renderer{
		class BREAK_API_EX DXManager:public Infrastructure::IGXManager{
		protected:
			//swap chain to control frame buffer
			IDXGISwapChain* _swapChain;
			//DX device
			ID3D11Device* _device;
			//DX Context
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
			D3D11_RASTERIZER_DESC _rasterStateDesc;
			//GPU Info
			bool _vsync;
			unsigned int _videoCardMemory;
			char _videoCardDescription[128];
		private:
			bool initD3D(HWND hWnd, int Width, int Height, bool vsync, bool fullscreen );
			//window start
			void windowStart();
			//closes DX
			void cleanD3D();

			static LRESULT CALLBACK WindowProc(HWND hWnd, u32 message, WPARAM wParam, LPARAM lParam);

			//takes element type and returns element DX format
			DXGI_FORMAT getFormat(GXWrapper::MemoryElement& element);
			D3D11_TEXTURE_ADDRESS_MODE getAddressMode(GXWrapper::TextureAddressMode address);
			D3D11_COMPARISON_FUNC getCompareFunc(GXWrapper::CompareFunction func);
			D3D11_FILTER getFilter(GXWrapper::TextureFilter filter);
		public:
			DXManager();
			~DXManager();

			bool init(Infrastructure::ApplicationPtr app);
			void start();
			void clearBuffer();
			virtual void setRasterMode(Infrastructure::RasterMode) override;
			virtual void setCullMode(Infrastructure::CullMode)override;
			void swapBuffer();
			void setCursorPostion(glm::uvec2 val);

			bool createVertexBuffer(Infrastructure::GPUResource* buffer) override;
			virtual Infrastructure::IGPUHandlePtr vm_createVertexBuffer(Renderer::GPU_ISA type, u32 size, void* data) override;

			bool createIndexBuffer(Infrastructure::GPUResource* buffer) override;
			virtual Infrastructure::IGPUHandlePtr vm_createIndexBuffer(Renderer::GPU_ISA type, u32 size, void* data) override;

			bool updateVertexBuffer(Infrastructure::GPUResource*,u32 offset,u32 size) override;
			virtual void vm_mapVertexBuffer(Infrastructure::IGPUHandle* handle, u32 size, void* data) override;

			bool updateIndexBuffer(Infrastructure::GPUResource* buffer, u32 offset, u32 size) override;
			virtual void vm_mapIndexBuffer(Infrastructure::IGPUHandle* handle, u32 size, void* data)override;

			bool deleteBuffer(Infrastructure::GPUResource* buffer) override;
			virtual bool vm_deleteBuffer(Infrastructure::IGPUHandle* handle)override;

			bool useVertexBuffer(Infrastructure::GPUResource* buffer) override;
			virtual void vm_bindVertexBuffer(Infrastructure::IGPUHandle* _handle, u32 stride)override;

			bool useIndexBuffer(Infrastructure::GPUResource* buffer) override;
			virtual void vm_bindIndexBuffer(Infrastructure::IGPUHandle* _handle) override;


			bool createUniformBuffer(Infrastructure::GPUResource* buffer) override;
			virtual Infrastructure::IGPUHandlePtr vm_createUniformBuffer(u32 size, void* data, u32 slot)override;

			bool useUniformBuffer(Infrastructure::GPUResource* buffer) override;
			virtual void vm_bindUniformBuffer(Infrastructure::IGPUHandle* _handle, Renderer::GPU_ISA shader, u32 slot)override;

			bool updateUniformBuffer(Infrastructure::GPUResource* buffer,u32 offset,u32 size) override;
			virtual void vm_mapUniformBuffer(Infrastructure::IGPUHandle* _handle,u32 size, void* data)override;

			bool createShader(Infrastructure::GPUResource* shader) override;
			virtual Infrastructure::IGPUHandlePtr vm_createProgram(std::string vertex,std::string pixel, GXWrapper::MemoryLayout* inputLayout)override;

			bool useShader(Infrastructure::GPUResource* shader) override;
			virtual void vm_bindShader(Infrastructure::IGPUHandle* _handle)override;

			bool deleteShader(Infrastructure::GPUResource* shader) override;
			virtual void vm_deleteShader(Infrastructure::IGPUHandle* _handle)override;

			virtual bool createTexture2D(Infrastructure::GPUResource* texture,GXWrapper::Image& img) override;
			virtual Infrastructure::IGPUHandlePtr vm_createTexture2D(GXWrapper::Image& img, bool mipmaps)override;

			virtual bool updateTexture2D(Infrastructure::GPUResource* texture,GXWrapper::Image& img) override;
			virtual void vm_mapTexture2D(Infrastructure::IGPUHandle* _handle, GXWrapper::Image& img)override;

			virtual bool deleteTexture2D(Infrastructure::GPUResource* texture) override;
			virtual void vm_deleteTexture2D(Infrastructure::IGPUHandle* _handle)override;

			virtual bool useTexture2D(Infrastructure::GPUResource* texture,unsigned int unit, GXWrapper::Shader::Type type) override;
			virtual void vm_bindTexture2D(Infrastructure::IGPUHandle* _handle, Renderer::GPU_ISA type, u32 unit)override;

			//geometry functions
			virtual bool createGeometry(GXWrapper::Geometry*);
			virtual Infrastructure::IGPUHandlePtr 
			vm_createGeometry(Infrastructure::IGPUHandle* vertex, Infrastructure::IGPUHandle* pixel, GXWrapper::MemoryLayout* input_layout)override;

			virtual bool drawGeometry(GXWrapper::Geometry*, GXWrapper::Primitive::Mode mode);

			virtual void 
			vm_draw(GXWrapper::Primitive::Type type, Infrastructure::IGPUHandle* geometry,
			Infrastructure::IGPUHandle* vertex_buffer, u32 vertices_count,
			GXWrapper::MemoryLayout* input_layout)override;

			virtual void 
			vm_drawIndexed(GXWrapper::Primitive::Type type, Infrastructure::IGPUHandle* geometry,
			Infrastructure::IGPUHandle* vertex_buffer, Infrastructure::IGPUHandle* index_buffer,
			u32 indices_count, GXWrapper::MemoryLayout* input_layout)override;


			virtual bool deleteGeometry(Infrastructure::GPUResource*);
			virtual void vm_deleteGeometry(Infrastructure::IGPUHandle* _handle)override;

			//sampler functions
			virtual bool createSamplerState(Infrastructure::GPUResource*) override;
			virtual Infrastructure::IGPUHandlePtr vm_createSampleState(GXWrapper::TextureAddressMode U, GXWrapper::TextureAddressMode V,
				GXWrapper::TextureAddressMode W, GXWrapper::TextureFilter filter,
			    GXWrapper::CompareFunction func, GXWrapper::Color* color)override;

			virtual bool useSamplerState(Infrastructure::GPUResource*,unsigned int slot, GXWrapper::Shader::Type) override;
			virtual void vm_bindSampler(Infrastructure::IGPUHandle* _handle, Renderer::GPU_ISA shader, u32 slot)override;

			virtual bool deleteSamplerState(Infrastructure::GPUResource*)override;
			virtual void vm_deleteSampler(Infrastructure::IGPUHandle* _handle)override;

			virtual bool applySamplerStateToTexture2D(Infrastructure::GPUResource* sampler, Infrastructure::GPUResource* texture)override;
			virtual void vm_applySamplerTexture2D(Infrastructure::IGPUHandle* sampler, Infrastructure::IGPUHandle* texture, bool mipmaps, GXWrapper::TextureAddressMode U,
			    GXWrapper::TextureAddressMode V, GXWrapper::TextureFilter filter, GXWrapper::CompareFunction func,
			    GXWrapper::Color border_color
				) override;
		};
	}
}
#endif