#ifdef _WIN32
#include "DXManager.h"
#include "Display.h"
#include "Engine.h"
#include "DXKeyboard.h"
#include "DXMouse.h"
#include <windowsx.h>
#include "DXBufferHandle.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "GPUException.h"
#include "DXShaderHandle.h"
#include "Shader.h"
#include "UniformBuffer.h"
#include <D3Dcompiler.h>
#include "Texture2D.h"
#include "DXTexture2DHandle.h"
//testing purpose headers
#include <iostream>
#include <DXSamplerHandle.h>
using namespace std;
//
using namespace Break;
using namespace Break::Renderer;
using namespace Break::Infrastructure;
using namespace Break::GXWrapper;

//linking libraries
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")

DXManager::DXManager(){
	_swapChain = NULL;
	_device = NULL;
	_deviceContext = NULL;
	_renderTargetView = NULL;
	_depthStencilBuffer = NULL;
	_depthStencilState = NULL;
	_depthStencilView = NULL;
	_rasterState = NULL;
	_vsync = false;
}
DXManager::~DXManager(){
	cleanD3D();
}

bool DXManager::init(ApplicationPtr app){
	//here comes the application pointer
	//you should take the IDisplay pointer and swap it with a similar Display<HWND> one with the same width, height, title
	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = this->WindowProc;
	wc.hInstance = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "WindowClass1";

	RegisterClassEx(&wc);

	RECT wr = { 0, 0, app->display->getWidth(), app->display->getHeight() };    // set the size, but not the position
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

	hWnd = CreateWindowEx(NULL,
		"WindowClass1",
		app->display->getTitle().c_str(),
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		NULL,
		NULL);
	ShowWindow(hWnd, SW_SHOW);

	// set up and initialize Direct3D

	Display<HWND>* d = new Display<HWND>(*app->display);
	d->setHandle(hWnd);
	app->display = IDisplayPtr(d);


	return this->initD3D(hWnd,app->display->getWidth(),app->display->getHeight(),_vsync,false);


}

bool DXManager::initD3D(HWND hWnd, int Width, int Height, bool vsync, bool fullscreen ){
	HRESULT result;
	IDXGIFactory* factory; //to create SwapChain..

	IDXGIAdapter* adapter; //check for graphics adapter (video card) availablty..

	IDXGIOutput* adapterOutput;

	unsigned int numModes, i, numerator, denominator, stringLength;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	int error;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Texture2D* backBufferPtr;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_VIEWPORT viewport;
	float fieldOfView, screenAspect;


	// Store the vsync setting.
	_vsync = vsync;

	// Create a DirectX graphics interface factory.
	//to create swapchain..
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if(FAILED(result))
	{
		return false;
	}

	// Use the factory to create an adapter for the primary graphics interface (video card).
	//enumrate video adabter
	result = factory->EnumAdapters(0, &adapter);
	if(FAILED(result))
	{
		return false;
	}


	// Enumerate the primary adapter output (monitor).
	result = adapter->EnumOutputs(0, &adapterOutput);
	if(FAILED(result))
	{
		return false;
	}

	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if(FAILED(result))
	{
		return false;
	}


	// Create a list to hold all the possible display modes for this monitor/video card combination.
	displayModeList = new DXGI_MODE_DESC[numModes];
	if(!displayModeList)
	{
		return false;
	}

	// Now fill the display mode list structures.
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if(FAILED(result))
	{
		return false;
	}

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	for(i=0; i<numModes; i++)
	{
		if(displayModeList[i].Width == (unsigned int)Width)
		{
			if(displayModeList[i].Height == (unsigned int)Height)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}


	// Get the adapter (video card) description.
	result = adapter->GetDesc(&adapterDesc);
	if(FAILED(result))
	{
		return false;
	}


	// Store the dedicated video card memory in megabytes.
	_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// Convert the name of the video card to a character array and store it.
	error = wcstombs_s(&stringLength, _videoCardDescription, 128, adapterDesc.Description, 128);
	if(error != 0)
	{
		return false;
	}


	// Release the display mode list.
	delete [] displayModeList;
	displayModeList = 0;

	// Release the adapter output.
	adapterOutput->Release();
	adapterOutput = 0;

	// Release the adapter.
	adapter->Release();
	adapter = 0;

	// Release the factory.
	factory->Release();
	factory = 0;


	// Initialize the swap chain description.
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Set to a single back buffer.
	swapChainDesc.BufferCount = 1;


	// Set the width and height of the back buffer.
	swapChainDesc.BufferDesc.Width = Width;
	swapChainDesc.BufferDesc.Height = Height;

	// Set regular 32-bit surface for the back buffer.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;


	// Set the refresh rate of the back buffer.
	if(_vsync)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}


	// Set the usage of the back buffer.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle for the window to render to.
	swapChainDesc.OutputWindow = hWnd;

	// Turn multisampling off.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	// Set to full screen or windowed mode.
	if(fullscreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}


	// Set the scan line ordering and scaling to unspecified.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	swapChainDesc.Flags = 0;

	// Set the feature level to DirectX 11.
	featureLevel = D3D_FEATURE_LEVEL_11_0;

	// Create the swap chain, Direct3D device, and Direct3D device context.
	result = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		&featureLevel,
		1, 
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&_swapChain,
		&_device,
		NULL,
		&_deviceContext);
	if(FAILED(result))
	{
		return false;
	}


	// Get the pointer to the back buffer.
	result = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
	if(FAILED(result))
	{
		return false;
	}

	// Create the render target view with the back buffer pointer.
	result = _device->CreateRenderTargetView(backBufferPtr, NULL, &_renderTargetView);
	if(FAILED(result))
	{
		return false;
	}

	// Release pointer to the back buffer as we no longer need it.
	backBufferPtr->Release();
	backBufferPtr = 0;


	// Initialize the description of the depth buffer.
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = Width;
	depthBufferDesc.Height = Height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;



	// Create the texture for the depth buffer using the filled out description.
	result = _device->CreateTexture2D(&depthBufferDesc, NULL, &_depthStencilBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;


	// Create the depth stencil state.
	result = _device->CreateDepthStencilState(&depthStencilDesc, &_depthStencilState);
	if(FAILED(result))
	{
		return false;
	}


	// Set the depth stencil state.
	_deviceContext->OMSetDepthStencilState(_depthStencilState, 1);


	// Initailze the depth stencil view.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	result = _device->CreateDepthStencilView(_depthStencilBuffer, &depthStencilViewDesc, &_depthStencilView);
	if(FAILED(result))
	{
		return false;
	}

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	_deviceContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);

	// Setup the raster description which will determine how and what polygons will be drawn.
	_rasterStateDesc.AntialiasedLineEnable = false;
	_rasterStateDesc.CullMode = D3D11_CULL_BACK;
	_rasterStateDesc.DepthBias = 0;
	_rasterStateDesc.DepthBiasClamp = 0.0f;
	_rasterStateDesc.DepthClipEnable = true;
	_rasterStateDesc.FillMode = D3D11_FILL_SOLID;
	_rasterStateDesc.FrontCounterClockwise = true;
	_rasterStateDesc.MultisampleEnable = true;
	_rasterStateDesc.ScissorEnable = false;
	_rasterStateDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	result = _device->CreateRasterizerState(&_rasterStateDesc, &_rasterState);
	if(FAILED(result))
	{
		return false;
	}

	// Now set the rasterizer state.
	_deviceContext->RSSetState(_rasterState);


	// Setup the viewport for rendering.
	viewport.Width = (float)Width;
	viewport.Height = (float)Height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	// Create the viewport.
	_deviceContext->RSSetViewports(1, &viewport);

	// Setup the projection matrix.
	fieldOfView = (float)(22/7) / 4.0f;
	screenAspect = (float)Width / (float)Height;

	D3D11_BLEND_DESC blendDesc;
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	
	ID3D11BlendState* blendState;
	_device->CreateBlendState(&blendDesc,&blendState);
	_deviceContext->OMSetBlendState(blendState,NULL,0xFFFFFF);
	return true;
}
void DXManager::windowStart(){
	// enter the main loop:
	MSG msg;

	while(TRUE)
	{

		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if(msg.message == WM_QUIT)
			{
				break;
			}
		}else{
			//checks if engine is shutting down;
			if(Engine::Instance->_shutdown)
				break;
			Engine::Instance->gameloop();
		}
	}
}
void DXManager::start(){
	windowStart();
	return;
}

void DXManager::clearBuffer(){
	float c[4] = {0,0,0,0};
	_deviceContext->ClearRenderTargetView(_renderTargetView,c);
	_deviceContext->ClearDepthStencilView(_depthStencilView,D3D11_CLEAR_DEPTH,1.0f,0);
}

void DXManager::setRasterMode(RasterMode mode)
{
	switch(mode)
	{
	case RasterMode::FILL:
		_rasterStateDesc.FillMode = D3D11_FILL_SOLID;
		_rasterState->Release();
		_device->CreateRasterizerState(&_rasterStateDesc,&_rasterState);
		_deviceContext->RSSetState(_rasterState);
		break;
	case RasterMode::WIREFRAME:
		_rasterStateDesc.FillMode = D3D11_FILL_WIREFRAME;
		_rasterState->Release();
		_device->CreateRasterizerState(&_rasterStateDesc,&_rasterState);
		_deviceContext->RSSetState(_rasterState);
		break;
	default: break;
	}
}

void DXManager::setCullMode(CullMode mode)
{
	switch(mode)
	{
	case CullMode::NONE:
		_rasterStateDesc.CullMode = D3D11_CULL_NONE;
		_rasterState->Release();
		_device->CreateRasterizerState(&_rasterStateDesc,&_rasterState);
		_deviceContext->RSSetState(_rasterState);
		break;
	case CullMode::FRONT:
		_rasterStateDesc.CullMode = D3D11_CULL_FRONT;
		_rasterState->Release();
		_device->CreateRasterizerState(&_rasterStateDesc,&_rasterState);
		_deviceContext->RSSetState(_rasterState);
		break;
	case CullMode::BACK:
		_rasterStateDesc.CullMode = D3D11_CULL_BACK;
		_rasterState->Release();
		_device->CreateRasterizerState(&_rasterStateDesc,&_rasterState);
		_deviceContext->RSSetState(_rasterState);
		break;
	default: break;
	}
}

void DXManager::swapBuffer(){
	if(_vsync){
		_swapChain->Present(1,0);
	}else{
		_swapChain->Present(0,0);
	}
}
void DXManager::setCursorPostion(glm::uvec2 val){
	Display<HWND>* d = dynamic_cast<Display<HWND>*>(Engine::Instance->Application->display.get());
	HWND hnd = d->getHandle();
	POINT pt;
	pt.x = val.x;
	pt.y = val.y;
	if(hnd){
		ClientToScreen(hnd,&pt);
		SetCursorPos(pt.x,pt.y);
	}
	d = NULL;
}
void DXManager::cleanD3D(){
	if(_swapChain)
	{
		_swapChain->SetFullscreenState(false, NULL);
	}

	if(_rasterState)
	{
		_rasterState->Release();
		_rasterState = 0;
	}

	if(_depthStencilView)
	{
		_depthStencilView->Release();
		_depthStencilView = 0;
	}

	if(_depthStencilState)
	{
		_depthStencilState->Release();
		_depthStencilState = 0;
	}

	if(_depthStencilBuffer)
	{
		_depthStencilBuffer->Release();
		_depthStencilBuffer = 0;
	}

	if(_renderTargetView)
	{
		_renderTargetView->Release();
		_renderTargetView = 0;
	}

	if(_deviceContext)
	{
		_deviceContext->Release();
		_deviceContext = 0;
	}

	if(_device)
	{
		_device->Release();
		_device = 0;
	}

	if(_swapChain)
	{
		_swapChain->Release();
		_swapChain = 0;
	}
}
//Event Handler for this Window..
/////////////////////////////////////
LRESULT CALLBACK DXManager::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		} break;
	case WM_KEYDOWN:
		Input::DXKeyboard::keyboardDown(wParam);
		break;
	case WM_KEYUP:
		Input::DXKeyboard::keyboardUp(wParam);
		break;
	case WM_LBUTTONDOWN:
			Input::DXMouse::mouseButton(0,0);
		break;
	case WM_LBUTTONUP:
			Input::DXMouse::mouseButton(0,1);
		break;
	case WM_RBUTTONDOWN:
			Input::DXMouse::mouseButton(2,0);
		break;
	case WM_RBUTTONUP:
			Input::DXMouse::mouseButton(2,1);
		break;
	case WM_MBUTTONDOWN:
			Input::DXMouse::mouseButton(1,0);
		break;
	case WM_MBUTTONUP:
			Input::DXMouse::mouseButton(1,1);
		break;
	case WM_MOUSEMOVE:
			Input::DXMouse::mouseMove(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
		break;
	}

	return DefWindowProc (hWnd, message, wParam, lParam);
}

bool DXManager::createVertexBuffer(GPUResource* buffer){

	GXWrapper::VertexBuffer* VBuffer = dynamic_cast<GXWrapper::VertexBuffer*>(buffer);

	auto handle = make_shared<DXBufferHandle>();

	CD3D11_BUFFER_DESC bufferDESC;
	bufferDESC.ByteWidth = VBuffer->getSize();
	bufferDESC.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDESC.MiscFlags = 0;

	switch (VBuffer->getType())
	{
	//dynamic
	case 0:
		bufferDESC.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDESC.Usage = D3D11_USAGE_DYNAMIC;
		break;
	//static
	case 1:
		bufferDESC.CPUAccessFlags = 0;
		bufferDESC.Usage = D3D11_USAGE_IMMUTABLE;
		break;
	default:
		break;
	}

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = VBuffer->getData();
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	HRESULT res = _device->CreateBuffer(&bufferDESC,&initData,&handle->DXBuffer);

	VBuffer->_handle = handle;

	if(FAILED(res))
		return false;
	else
		return true;
}

IGPUHandlePtr DXManager::vm_createVertexBuffer(GPU_ISA type, u32 size, void* data)
{

	auto handle = make_shared<DXBufferHandle>();

	CD3D11_BUFFER_DESC bufferDESC;
	bufferDESC.ByteWidth = size;
	bufferDESC.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDESC.MiscFlags = 0;

	switch (type)
	{
	//dynamic
	case GPU_ISA::DYNAMIC:
		bufferDESC.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDESC.Usage = D3D11_USAGE_DYNAMIC;
		break;
	//static
	case GPU_ISA::STATIC:
		bufferDESC.CPUAccessFlags = 0;
		bufferDESC.Usage = D3D11_USAGE_IMMUTABLE;
		break;
	default:
		return nullptr;
		break;
	}

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = data;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	HRESULT res = _device->CreateBuffer(&bufferDESC,&initData,&handle->DXBuffer);


	if(FAILED(res))
		return nullptr;
	else
		return handle;
}

bool DXManager::createIndexBuffer(GPUResource* buffer){
	
	GXWrapper::IndexBuffer* IBuffer = dynamic_cast<GXWrapper::IndexBuffer*>(buffer);

	auto handle = make_shared<DXBufferHandle>();

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = IBuffer->getSize();
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.MiscFlags = 0;

	switch (IBuffer->getType())
	{
		//dynamic
	case 0:
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		break;
		//static
	case 1:
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		break;
	default:
		break;
	}

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = IBuffer->getData();
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	HRESULT res = _device->CreateBuffer(&bufferDesc,&initData,&handle->DXBuffer);

	IBuffer->_handle = handle;
	if(FAILED(res))
		return false;
	else
		return true;

}

Infrastructure::IGPUHandlePtr DXManager::vm_createIndexBuffer(GPU_ISA type, u32 size, void* data)
{

	auto handle = make_shared<DXBufferHandle>();

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = size;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.MiscFlags = 0;

	switch (type)
	{
		//dynamic
	case GPU_ISA::DYNAMIC:
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		break;
		//static
	case GPU_ISA::STATIC:
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		break;
	default:
		break;
	}

	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = data;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	HRESULT res = _device->CreateBuffer(&bufferDesc,&initData,&handle->DXBuffer);

	if(FAILED(res))
		return nullptr;
	else
		return handle;
}

bool DXManager::updateVertexBuffer(GPUResource* buffer,unsigned int offset,unsigned int size){
	auto VBuffer = dynamic_cast<GXWrapper::VertexBuffer*>(buffer);

	if(VBuffer->getType() == VertexBuffer::STATIC)
		throw GPUException("Cannot Map Vertex Buffer: Buffer type is not dynamic");

	DXBufferHandle* handle = dynamic_cast<DXBufferHandle*>(VBuffer->_handle.get());

	D3D11_MAPPED_SUBRESOURCE mappedData;
	_deviceContext->Map(handle->DXBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);

	//memcpy(mappedData.pData,VBuffer->getData(offset),size);
	auto cpySize = VBuffer->getSize();
	memcpy(mappedData.pData,VBuffer->getData(),cpySize);

	_deviceContext->Unmap(handle->DXBuffer,0);
	return true;
}

void DXManager::vm_mapVertexBuffer(Infrastructure::IGPUHandle* _handle, u32 size, void* data)
{

	DXBufferHandle* handle = dynamic_cast<DXBufferHandle*>(_handle);

	D3D11_MAPPED_SUBRESOURCE mappedData;
	_deviceContext->Map(handle->DXBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);

	//memcpy(mappedData.pData,VBuffer->getData(offset),size);
	auto cpySize = size;
	memcpy(mappedData.pData,data,cpySize);

	_deviceContext->Unmap(handle->DXBuffer,0);
}

void DXManager::vm_mapIndexBuffer(Infrastructure::IGPUHandle* _handle, u32 size, void* data)
{

	DXBufferHandle* handle = dynamic_cast<DXBufferHandle*>(_handle);

	D3D11_MAPPED_SUBRESOURCE mappedData;
	_deviceContext->Map(handle->DXBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);

	//memcpy(mappedData.pData,IBuffer->getData(offset),size);
	auto cpySize = size;
	memcpy(mappedData.pData,data,cpySize);

	_deviceContext->Unmap(handle->DXBuffer,0);
}

bool DXManager::updateIndexBuffer(GPUResource* buffer, unsigned int offset, unsigned int size){
	auto IBuffer = dynamic_cast<GXWrapper::IndexBuffer*>(buffer);

	if(IBuffer->getType() == VertexBuffer::STATIC)
		throw GPUException("Cannot Map Index Buffer: Buffer type is not dynamic");

	DXBufferHandle* handle = dynamic_cast<DXBufferHandle*>(IBuffer->_handle.get());

	D3D11_MAPPED_SUBRESOURCE mappedData;
	_deviceContext->Map(handle->DXBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);

	//memcpy(mappedData.pData,IBuffer->getData(offset),size);
	auto cpySize = IBuffer->getSize();
	memcpy(mappedData.pData,IBuffer->getData(),cpySize);

	_deviceContext->Unmap(handle->DXBuffer,0);
	return true;
}

bool DXManager::deleteBuffer(GPUResource* buffer){
	auto handle = dynamic_cast<DXBufferHandle*>(buffer->_handle.get());

	handle->DXBuffer->Release();
	return true;
}

bool DXManager::vm_deleteBuffer(Infrastructure::IGPUHandle* _handle)
{
	auto handle = dynamic_cast<DXBufferHandle*>(_handle);

	handle->DXBuffer->Release();
	return true;
}

bool DXManager::useVertexBuffer(GPUResource* buffer){
	auto VBuffer = dynamic_cast<VertexBuffer*>(buffer);
	auto handle = dynamic_cast<DXBufferHandle*>(buffer->_handle.get());

	unsigned int stride = VBuffer->getLayout().getSize();
	unsigned int offset = 0;
	_deviceContext->IASetVertexBuffers(0,1,&handle->DXBuffer,&stride,&offset);

	return true;
}

void DXManager::vm_bindVertexBuffer(Infrastructure::IGPUHandle* _handle, u32 _stride)
{
	auto handle = dynamic_cast<DXBufferHandle*>(_handle);

	unsigned int stride = _stride;
	unsigned int offset = 0;
	_deviceContext->IASetVertexBuffers(0,1,&handle->DXBuffer,&stride,&offset);
}

bool DXManager::useIndexBuffer(GPUResource* buffer){
	auto handle = dynamic_cast<DXBufferHandle*>(buffer->_handle.get());
	_deviceContext->IASetIndexBuffer(handle->DXBuffer,DXGI_FORMAT_R32_UINT,0);
	return true;
}

void DXManager::vm_bindIndexBuffer(Infrastructure::IGPUHandle* _handle)
{
	auto handle = dynamic_cast<DXBufferHandle*>(_handle);
	_deviceContext->IASetIndexBuffer(handle->DXBuffer,DXGI_FORMAT_R32_UINT,0);
}

DXGI_FORMAT DXManager::getFormat(MemoryElement& element){
	switch (element.type)
	{
	case MemoryElement::BOOL:
		return DXGI_FORMAT_R32_UINT;
		break;
	case  MemoryElement::FLOAT:
		return DXGI_FORMAT_R32_FLOAT;
		break;
	case MemoryElement::INT:
		return DXGI_FORMAT_R32_SINT;
		break;
	case MemoryElement::VEC2:
		return DXGI_FORMAT_R32G32_FLOAT;
		break;
	case MemoryElement::VEC3:
		return DXGI_FORMAT_R32G32B32_FLOAT;
		break;
	case MemoryElement::VEC4:
		return DXGI_FORMAT_R32G32B32A32_FLOAT;
		break;
	case MemoryElement::MAT3:
		return DXGI_FORMAT_UNKNOWN;
		break;
	case MemoryElement::MAT4:
		return DXGI_FORMAT_UNKNOWN;
		break;
	default:
		break;
	}
}

D3D11_TEXTURE_ADDRESS_MODE DXManager::getAddressMode(TextureAddressMode address)
{
	switch(address)
	{
	case TextureAddressMode::WRAP:
		return D3D11_TEXTURE_ADDRESS_WRAP;
		break;
	case TextureAddressMode::CLAMP:
		return D3D11_TEXTURE_ADDRESS_CLAMP;
		break;
	case TextureAddressMode::MIRROR:
		return D3D11_TEXTURE_ADDRESS_MIRROR;
		break;
	case TextureAddressMode::BORDER:
		return D3D11_TEXTURE_ADDRESS_BORDER;
		break;
	default: break;
	}
}

D3D11_COMPARISON_FUNC DXManager::getCompareFunc(CompareFunction func)
{
	switch (func)
	{
	case CompareFunction::ALWAYS:
		return D3D11_COMPARISON_ALWAYS;
		break;
	case CompareFunction::NEVER:
		return D3D11_COMPARISON_NEVER;
		break;
	case CompareFunction::LESS:
		return D3D11_COMPARISON_LESS;
		break;
	case CompareFunction::LESS_EQUAL:
		return D3D11_COMPARISON_LESS_EQUAL;
		break;
	case CompareFunction::EQUAL: 
		return D3D11_COMPARISON_EQUAL;
		break;
	case CompareFunction::GREATER_EQUAL:
		return D3D11_COMPARISON_GREATER_EQUAL;
		break;
	case CompareFunction::GREATER:
		return D3D11_COMPARISON_GREATER;
		break;
	case CompareFunction::NOT_EQUAL:
		return D3D11_COMPARISON_NOT_EQUAL;
		break;
	default: break;
	}
}

D3D11_FILTER DXManager::getFilter(TextureFilter filter)
{
	switch(filter)
	{
	case TextureFilter::LINEAR: 
		return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		break;
	case TextureFilter::POINT: 
		return D3D11_FILTER_MIN_MAG_MIP_POINT;
		break;
	case TextureFilter::ANISOTROPIC: 
		return D3D11_FILTER_ANISOTROPIC;
		break;
	case TextureFilter::LINEAR_MIP_POINT: 
		return D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		break;
	case TextureFilter::POINT_MIP_LINEAR:
		return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
		break;
	case TextureFilter::MIN_LINEAR_MAG_POINT_MIP_LINEAR:
		return D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
		break;
	case TextureFilter::MIN_LINEAR_MAG_POINT_MIP_POINT: 
		return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		break;
	case TextureFilter::MIN_POINT_MAG_LINEAR_MIP_LINEAR:
		return D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		break;
	case TextureFilter::MIN_POINT_MAG_LINEAR_MIP_POINT:
		return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
		break;
	default:
		return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		break;
	}
}

bool DXManager::createShader(GPUResource* shader){
	auto program = dynamic_cast<GXWrapper::Shader*>(shader);
	
	auto handle = make_shared<DXShaderHandle>();

	HRESULT res;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC* layout;
	unsigned int nElements;

	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	res = D3DCompile(program->_vs.c_str(),program->_vs.size(),"VS",NULL,NULL,"main",
			"vs_4_0",D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY,NULL,&vertexShaderBuffer,&errorMessage);

	if(FAILED(res)){
		if(errorMessage){
			cout<<(char*)errorMessage->GetBufferPointer()<<endl;
		}
		return false;
	}

	res = D3DCompile(program->_ps.c_str(),program->_ps.size(),"PS",NULL,NULL,"main",
		"ps_4_0",D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY,NULL,&pixelShaderBuffer,&errorMessage);

	if(FAILED(res)){
		if(errorMessage){
			cout<<(char*)errorMessage->GetBufferPointer()<<endl;
		}
		return false;
	}

	res = _device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),vertexShaderBuffer->GetBufferSize(),
		NULL, &handle->vertexShader);

	if(FAILED(res)){
		return false;
	}

	res = _device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),pixelShaderBuffer->GetBufferSize(),NULL,&handle->pixelShader);
	if(FAILED(res)){
		return false;
	}

	layout = new D3D11_INPUT_ELEMENT_DESC[program->_inputLayout.getElementCount()];

	for(int i=0;i<program->_inputLayout.getElementCount();i++){
		layout[i].SemanticName = program->_inputLayout.elements[i].semantic.c_str();
		layout[i].SemanticIndex = 0;
		layout[i].Format = getFormat(program->_inputLayout.elements[i]);
		layout[i].InputSlot = 0;
		layout[i].AlignedByteOffset = program->_inputLayout.elements[i].offset;
		layout[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		layout[i].InstanceDataStepRate = 0;
	}

	res = _device->CreateInputLayout(layout,program->_inputLayout.getElementCount(),vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(),&handle->inputLayout);

	if(FAILED(res)){
		std::cerr<<"Shader Cannot create input layout"<<std::endl;
		return false;
	}

	vertexShaderBuffer->Release();
	vertexShaderBuffer =0;
	pixelShaderBuffer->Release();
	pixelShaderBuffer=0;

	program->_handle = handle;
	//res = D3DX11CompileFromMemory(program->_vs,program->_vs.size(),);
	//compile pixel shader
	//create vertex shader
	//create pixel shader
	//create layout

	return true;
}

IGPUHandlePtr DXManager::vm_createProgram(std::string vertex, std::string pixel, GXWrapper::MemoryLayout* inputLayout)
{	
	auto handle = make_shared<DXShaderHandle>();

	HRESULT res;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC* layout;
	unsigned int nElements;

	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	res = D3DCompile(vertex.c_str(),vertex.size(),"VS",NULL,NULL,"main",
			"vs_4_0",D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY,NULL,&vertexShaderBuffer,&errorMessage);

	if(FAILED(res)){
		if(errorMessage){
			cout<<(char*)errorMessage->GetBufferPointer()<<endl;
		}
		throw GPUException("Cannot compile vertex shader");
	}

	res = D3DCompile(pixel.c_str(),pixel.size(),"PS",NULL,NULL,"main",
		"ps_4_0",D3DCOMPILE_ENABLE_BACKWARDS_COMPATIBILITY,NULL,&pixelShaderBuffer,&errorMessage);

	if(FAILED(res)){
		if(errorMessage){
			cout<<(char*)errorMessage->GetBufferPointer()<<endl;
		}
		throw GPUException("Cannot compile pixel shader");
	}

	res = _device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),vertexShaderBuffer->GetBufferSize(),
		NULL, &handle->vertexShader);

	if(FAILED(res)){
		throw GPUException("Cannot generate vertex shader");
	}

	res = _device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),pixelShaderBuffer->GetBufferSize(),NULL,&handle->pixelShader);
	if(FAILED(res)){
		throw GPUException("Cannot generate pixel shader");
	}

	layout = new D3D11_INPUT_ELEMENT_DESC[inputLayout->getElementCount()];

	for(int i=0;i<inputLayout->getElementCount();i++){
		layout[i].SemanticName = inputLayout->elements[i].semantic.c_str();
		layout[i].SemanticIndex = 0;
		layout[i].Format = getFormat(inputLayout->elements[i]);
		layout[i].InputSlot = 0;
		layout[i].AlignedByteOffset = inputLayout->elements[i].offset;
		layout[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		layout[i].InstanceDataStepRate = 0;
	}

	res = _device->CreateInputLayout(layout,inputLayout->getElementCount(),vertexShaderBuffer->GetBufferPointer(),
			vertexShaderBuffer->GetBufferSize(),&handle->inputLayout);

	if(FAILED(res)){
		throw GPUException("Cannot create input layout");
	}

	vertexShaderBuffer->Release();
	vertexShaderBuffer =0;
	pixelShaderBuffer->Release();
	pixelShaderBuffer=0;

	return handle;
	//res = D3DX11CompileFromMemory(program->_vs,program->_vs.size(),);
	//compile pixel shader
	//create vertex shader
	//create pixel shader
	//create layout
}

bool DXManager::useShader(GPUResource* shader){
	auto handle = dynamic_cast<DXShaderHandle*>(shader->_handle.get());

	_deviceContext->IASetInputLayout(handle->inputLayout);
	_deviceContext->VSSetShader(handle->vertexShader,NULL,0);
	_deviceContext->PSSetShader(handle->pixelShader,NULL,0);

	return true;
}

void DXManager::vm_bindShader(Infrastructure::IGPUHandle* _handle)
{
	auto handle = dynamic_cast<DXShaderHandle*>(_handle);

	_deviceContext->IASetInputLayout(handle->inputLayout);
	_deviceContext->VSSetShader(handle->vertexShader,NULL,0);
	_deviceContext->PSSetShader(handle->pixelShader,NULL,0);
}

bool DXManager::deleteShader(GPUResource* shader){
	auto handle = dynamic_cast<DXShaderHandle*>(shader->_handle.get());

	if(handle->inputLayout)
	{
		handle->inputLayout->Release();
		handle->inputLayout = 0;
	}
	if(handle->vertexShader)
	{
		handle->vertexShader->Release();
		handle->vertexShader = 0;
	}
	if(handle->pixelShader)
	{
		handle->pixelShader->Release();
		handle->pixelShader = 0;
	}
	return true;
}

void DXManager::vm_deleteShader(Infrastructure::IGPUHandle* _handle)
{
	auto handle = dynamic_cast<DXShaderHandle*>(_handle);

	if(handle->inputLayout)
	{
		handle->inputLayout->Release();
		handle->inputLayout = 0;
	}
	if(handle->vertexShader)
	{
		handle->vertexShader->Release();
		handle->vertexShader = 0;
	}
	if(handle->pixelShader)
	{
		handle->pixelShader->Release();
		handle->pixelShader = 0;
	}
}

bool DXManager::createUniformBuffer(GPUResource* buffer){
	auto UBuffer = dynamic_cast<GXWrapper::UniformBuffer*>(buffer);

	auto handle = make_shared<DXBufferHandle>();

	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.ByteWidth = UBuffer->getSize();
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;


	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = UBuffer->getData();
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	auto res = _device->CreateBuffer(&desc,&initData,&handle->DXBuffer);

	UBuffer->_handle = handle;

	if(FAILED(res))
		return false;
	else
		return true;
}

Infrastructure::IGPUHandlePtr DXManager::vm_createUniformBuffer(u32 size, void* data, u32 slot)
{

	auto handle = make_shared<DXBufferHandle>();

	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.ByteWidth = size;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;


	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = data;
	initData.SysMemPitch = 0;
	initData.SysMemSlicePitch = 0;

	auto res = _device->CreateBuffer(&desc,&initData,&handle->DXBuffer);

	if(FAILED(res))
		return nullptr;
	else
		return handle;
}

bool DXManager::updateUniformBuffer(GPUResource* buffer,unsigned int offset,unsigned int size){
	auto UBuffer = dynamic_cast<GXWrapper::UniformBuffer*>(buffer);

	DXBufferHandle* handle = dynamic_cast<DXBufferHandle*>(UBuffer->_handle.get());

	D3D11_MAPPED_SUBRESOURCE mappedData;
	_deviceContext->Map(handle->DXBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);

	if(!mappedData.pData)
		return false;
	//memcpy(mappedData.pData,UBuffer->getData(offset),size);
	memcpy(mappedData.pData,UBuffer->getData(),UBuffer->getSize());

	_deviceContext->Unmap(handle->DXBuffer,0);
	return true;
}

void DXManager::vm_mapUniformBuffer(Infrastructure::IGPUHandle* _handle, u32 size, void* data)
{

	DXBufferHandle* handle = dynamic_cast<DXBufferHandle*>(_handle);

	D3D11_MAPPED_SUBRESOURCE mappedData;
	_deviceContext->Map(handle->DXBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);

	if(!mappedData.pData)
		throw GPUException("Cannot map uniform buffer");
	//memcpy(mappedData.pData,UBuffer->getData(offset),size);
	memcpy(mappedData.pData,data,size);

	_deviceContext->Unmap(handle->DXBuffer,0);
}

bool DXManager::useUniformBuffer(GPUResource* buffer){
	auto UBuffer = dynamic_cast<GXWrapper::UniformBuffer*>(buffer);
	auto handle = dynamic_cast<DXBufferHandle*>(UBuffer->_handle.get());
	
	if(UBuffer->_shader == Shader::VERTEX){
		_deviceContext->VSSetConstantBuffers(UBuffer->_slot,1,&handle->DXBuffer);
	}else if(UBuffer->_shader == Shader::PIXEL){
		_deviceContext->PSSetConstantBuffers(UBuffer->_slot,1,&handle->DXBuffer);
	}else
		return false;

	return true;
}

void DXManager::vm_bindUniformBuffer(Infrastructure::IGPUHandle* _handle, Renderer::GPU_ISA shader, u32 slot)
{
	auto handle = dynamic_cast<DXBufferHandle*>(_handle);
	
	if(shader == GPU_ISA::VERTEX_SHADER){
		_deviceContext->VSSetConstantBuffers(slot,1,&handle->DXBuffer);
	}else if(shader == GPU_ISA::PIXEL_SHADER){
		_deviceContext->PSSetConstantBuffers(slot,1,&handle->DXBuffer);
	}else
		throw GPUException("Cannot bind uniform buffer to shader");

}

bool DXManager::createTexture2D(GPUResource* texture,Image& img){
	auto tex = dynamic_cast<Texture2D*>(texture);

	auto handle = make_shared<DXTexture2DHandle>();

	D3D11_TEXTURE2D_DESC desc;
	desc.ArraySize = 1;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MipLevels = 1;
	desc.MiscFlags = 0;
	desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.Width = img.getWidth();
	desc.Height = img.getHeight();
	desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;

	D3D11_SUBRESOURCE_DATA descData;
	//ZeroMemory(&descData,sizeof(D3D11_SUBRESOURCE_DATA));
	descData.pSysMem = img.getPixels();
	descData.SysMemPitch = img.getWidth()*sizeof(Pixel);
	descData.SysMemSlicePitch = img.getSize();
	auto res = _device->CreateTexture2D(&desc,&descData,&handle->texture); 
	if(FAILED(res)){
		cout<<res<<endl;
		return false;
	}
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;
	res = _device->CreateShaderResourceView(handle->texture,&srvDesc,&handle->resourceView);
	if(FAILED(res)){
		cout<<res<<endl;
		return false;
	}
	if(tex->usingMipMaps())
		_deviceContext->GenerateMips(handle->resourceView);

	tex->_handle = handle;
	return true;
}

Infrastructure::IGPUHandlePtr DXManager::vm_createTexture2D(GXWrapper::Image& img, bool mipmaps)
{

	auto handle = make_shared<DXTexture2DHandle>();

	D3D11_TEXTURE2D_DESC desc;
	desc.ArraySize = 1;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MipLevels = 1;
	desc.MiscFlags = 0;
	desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.Width = img.getWidth();
	desc.Height = img.getHeight();
	desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;

	D3D11_SUBRESOURCE_DATA descData;
	//ZeroMemory(&descData,sizeof(D3D11_SUBRESOURCE_DATA));
	descData.pSysMem = img.getPixels();
	descData.SysMemPitch = img.getWidth()*sizeof(Pixel);
	descData.SysMemSlicePitch = img.getSize();
	auto res = _device->CreateTexture2D(&desc,&descData,&handle->texture); 
	if(FAILED(res)){
		cout<<res<<endl;
		throw GPUException("Cannot create texture2D");
	}
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;
	res = _device->CreateShaderResourceView(handle->texture,&srvDesc,&handle->resourceView);
	if(FAILED(res)){
		cout<<res<<endl;
		throw GPUException("Cannot create shader resource from texture2D");
	}
	if(mipmaps)
		_deviceContext->GenerateMips(handle->resourceView);

	return handle;
}

bool DXManager::updateTexture2D(GPUResource* texture, Image& img)
{
	auto handle = dynamic_cast<DXTexture2DHandle*>(texture->_handle.get());

	D3D11_MAPPED_SUBRESOURCE mappedData;
	_deviceContext->Map(handle->texture, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);

	if(!mappedData.pData)
		return false;
	//memcpy(mappedData.pData,UBuffer->getData(offset),size);
	memcpy(mappedData.pData,img.getPixels(),img.getSize());

	_deviceContext->Unmap(handle->texture,0);
	return true;

}

void DXManager::vm_mapTexture2D(Infrastructure::IGPUHandle* _handle, GXWrapper::Image& img)
{
	auto handle = dynamic_cast<DXTexture2DHandle*>(_handle);

	D3D11_MAPPED_SUBRESOURCE mappedData;
	_deviceContext->Map(handle->texture, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);

	if(!mappedData.pData)
		throw GPUException("Cannot map texture2D");
	//memcpy(mappedData.pData,UBuffer->getData(offset),size);
	memcpy(mappedData.pData,img.getPixels(),img.getSize());

	_deviceContext->Unmap(handle->texture,0);
}

bool DXManager::deleteTexture2D(GPUResource* texture)
{
	auto handle = dynamic_cast<DXTexture2DHandle*>(texture->_handle.get());

	if(handle->texture)
	{
		handle->texture->Release();
		handle->texture = 0;
	}

	if(handle->resourceView)
	{
		handle->resourceView->Release();
		handle->resourceView = 0;
	}
	return true;
}

void DXManager::vm_deleteTexture2D(Infrastructure::IGPUHandle* _handle)
{
	auto handle = dynamic_cast<DXTexture2DHandle*>(_handle);

	if(handle->texture)
	{
		handle->texture->Release();
		handle->texture = 0;
	}

	if(handle->resourceView)
	{
		handle->resourceView->Release();
		handle->resourceView = 0;
	}
}

bool DXManager::useTexture2D(GPUResource* texture, unsigned unit, Shader::Type type)
{
	auto handle = dynamic_cast<DXTexture2DHandle*>(texture->_handle.get());

	switch(type)
	{
	case Shader::NONE:
		return false;
		break;
	case Shader::VERTEX:
		_deviceContext->VSSetShaderResources(unit,1,&handle->resourceView);
		return true;
		break;
	case Shader::PIXEL:
		_deviceContext->PSSetShaderResources(unit,1,&handle->resourceView);
		return true;
		break;
	default:
		return false;
		break;
	}
}

void DXManager::vm_bindTexture2D(Infrastructure::IGPUHandle* _handle, Renderer::GPU_ISA type, u32 unit)
{
	auto handle = dynamic_cast<DXTexture2DHandle*>(_handle);

	switch(type)
	{
	case GPU_ISA::VERTEX_SHADER:
		_deviceContext->VSSetShaderResources(unit,1,&handle->resourceView);
		break;
	case GPU_ISA::PIXEL_SHADER:
		_deviceContext->PSSetShaderResources(unit,1,&handle->resourceView);
		break;
	default:
		throw GPUException("unidentified shader type to bind texture to it");
		break;
	}
}

bool DXManager::createGeometry(Geometry*)
{
	return true;
}

Infrastructure::IGPUHandlePtr DXManager::vm_createGeometry(Infrastructure::IGPUHandle* vertex, Infrastructure::IGPUHandle* pixel, GXWrapper::MemoryLayout* input_layout)
{
	return make_shared<IGPUHandle>();
}

bool DXManager::drawGeometry(Geometry* geometry, Primitive::Mode mode)
{
	auto geo = geometry;

	auto geoData = geo->_geometryData;

	if(geoData.primitive == 0)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	if(geoData.primitive == 1)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	if(geoData.primitive == 2)
		_deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	if(geoData.primitive == 3)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	if(geoData.primitive == 4)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if(geoData.primitive == 5)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	if(geoData.primitive == 6)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ);




	switch (mode)
	{
	case 0:     /*normal drawing*/

		geoData.vertices->use();
		_deviceContext->Draw(geoData.verticesCount,0);
		break;


	case 1:     /*indexed drawing*/

		/*   third paramater in this function ,,,
		This is the offset from the start of the vertex buffer to start drawing.
		You might have two index buffers, one describing a sphere, and one describing a box.
		But maybe you have both in a single vertex buffer, where the sphere is the first set of vertices in the vertex buffer,
		and the box is the second set.
		So to draw the box, you would need to set this third parameter to the number of vertices in your sphere,
		so that the box would be the first thing to start drawing.*/

		geoData.vertices->use();
		geoData.indices->use();
		_deviceContext->DrawIndexed(geoData.indicesCount,0,0);
		break;

	case 2:     /*normal instanced drawing*/
		geoData.vertices->use();
		geoData.indices->use();
		_deviceContext->DrawInstanced(geoData.verticesCount,geoData.instanceCount,0,0);
		break;

	case 3:     /*indexed instanced drawing*/
		geoData.vertices->use();
		geoData.indices->use();
		_deviceContext->DrawIndexedInstanced(geoData.indicesCount,geoData.instanceCount,0,0,0);
		break;
	}
	return true;
}

void DXManager::vm_draw(GXWrapper::Primitive::Type type, Infrastructure::IGPUHandle* geometry, Infrastructure::IGPUHandle* vertex_buffer, u32 vertices_count, GXWrapper::MemoryLayout* input_layout)
{

	if(type == 0)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	if(type == 1)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	if(type == 2)
		_deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	if(type == 3)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	if(type == 4)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if(type == 5)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	if(type == 6)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ);

	vm_bindVertexBuffer(vertex_buffer,input_layout->getSize());

	_deviceContext->Draw(vertices_count,0);
	
}

void DXManager::vm_drawIndexed(GXWrapper::Primitive::Type type, Infrastructure::IGPUHandle* geometry, Infrastructure::IGPUHandle* vertex_buffer, Infrastructure::IGPUHandle* index_buffer, u32 indices_count, GXWrapper::MemoryLayout* input_layout)
{

	if(type == 0)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	if(type == 1)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	if(type == 2)
		_deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	if(type == 3)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	if(type == 4)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if(type == 5)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	if(type == 6)
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ);




	vm_bindVertexBuffer(vertex_buffer,input_layout->getSize());
	vm_bindIndexBuffer(index_buffer);
	_deviceContext->DrawIndexed(indices_count,0,0);
}

bool DXManager::deleteGeometry(GPUResource*)
{
	return true; 
}

void DXManager::vm_deleteGeometry(Infrastructure::IGPUHandle* _handle)
{
	return;
}

bool DXManager::createSamplerState(GPUResource* gpSampler)
{

	auto sampler = dynamic_cast<SamplerState*>(gpSampler);
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.AddressU = getAddressMode(sampler->addressU);
	samplerDesc.AddressV = getAddressMode(sampler->addressV);
	samplerDesc.AddressW = getAddressMode(sampler->addressW);
	samplerDesc.ComparisonFunc = getCompareFunc(sampler->compareFunction);
	samplerDesc.Filter = getFilter(sampler->filter);
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.BorderColor[0] = sampler->borderColor.R;
	samplerDesc.BorderColor[1] = sampler->borderColor.G;
	samplerDesc.BorderColor[2] = sampler->borderColor.B;
	samplerDesc.BorderColor[3] = sampler->borderColor.A;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	auto handle = make_shared<DXSamplerHandle>();

	auto result = _device->CreateSamplerState(&samplerDesc,&handle->sampler);
	if(FAILED(result))
		return false;
	gpSampler->_handle = handle;
	return true;
}

Infrastructure::IGPUHandlePtr DXManager::vm_createSampleState(GXWrapper::TextureAddressMode U, GXWrapper::TextureAddressMode V, GXWrapper::TextureAddressMode W, GXWrapper::TextureFilter filter, GXWrapper::CompareFunction func, GXWrapper::Color* color)
{
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.AddressU = getAddressMode(U);
	samplerDesc.AddressV = getAddressMode(V);
	samplerDesc.AddressW = getAddressMode(W);
	samplerDesc.ComparisonFunc = getCompareFunc(func);
	samplerDesc.Filter = getFilter(filter);
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.BorderColor[0] = color->R;
	samplerDesc.BorderColor[1] = color->G;
	samplerDesc.BorderColor[2] = color->B;
	samplerDesc.BorderColor[3] = color->A;
	//samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	auto handle = make_shared<DXSamplerHandle>();

	auto result = _device->CreateSamplerState(&samplerDesc,&handle->sampler);
	if(FAILED(result))
		throw GPUException("Cannot create sampler");
	
	return handle;
}

bool DXManager::useSamplerState(GPUResource* gpSampler, unsigned slot, Shader::Type type)
{
	auto handle = dynamic_cast<DXSamplerHandle*>(gpSampler->_handle.get());

	if(type == Shader::VERTEX)
		_deviceContext->VSSetSamplers(slot,1,&handle->sampler);
	else if(type == Shader::PIXEL)
		_deviceContext->PSSetSamplers(slot,1,&handle->sampler);

	return true;
}

void DXManager::vm_bindSampler(Infrastructure::IGPUHandle* _handle, Renderer::GPU_ISA shader, u32 slot)
{
	auto handle = dynamic_cast<DXSamplerHandle*>(_handle);

	if(shader == GPU_ISA::VERTEX_SHADER)
		_deviceContext->VSSetSamplers(slot,1,&handle->sampler);
	else if(shader == GPU_ISA::PIXEL_SHADER)
		_deviceContext->PSSetSamplers(slot,1,&handle->sampler);
}

bool DXManager::deleteSamplerState(GPUResource* gpSampler)
{
	auto handle = dynamic_cast<DXSamplerHandle*>(gpSampler->_handle.get());
	handle->sampler->Release();
	handle->sampler = 0;
	return true;
}

void DXManager::vm_deleteSampler(Infrastructure::IGPUHandle* _handle)
{
	auto handle = dynamic_cast<DXSamplerHandle*>(_handle);
	handle->sampler->Release();
	handle->sampler = 0;
}

bool DXManager::applySamplerStateToTexture2D(GPUResource* sampler, GPUResource* texture)
{
	return true;
}

void DXManager::vm_applySamplerTexture2D(Infrastructure::IGPUHandle* sampler, Infrastructure::IGPUHandle* texture, bool mipmaps, GXWrapper::TextureAddressMode U, GXWrapper::TextureAddressMode V, GXWrapper::TextureFilter filter, GXWrapper::CompareFunction func, GXWrapper::Color border_color)
{
	return;
}
#endif