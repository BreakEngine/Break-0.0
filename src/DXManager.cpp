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
//testing purpose headers
#include <iostream>
using namespace std;
//
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

	RECT wr = { 0, 0, app->_display->getWidth(), app->_display->getHeight() };    // set the size, but not the position
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size

	hWnd = CreateWindowEx(NULL,
		"WindowClass1",
		app->_display->getTitle().c_str(),
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

	Display<HWND>* d = new Display<HWND>(*app->_display);
	d->setHandle(hWnd);
	app->_display = IDisplayPtr(d);


	return this->initD3D(hWnd,app->_display->getWidth(),app->_display->getHeight(),_vsync,false);


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
	D3D11_RASTERIZER_DESC rasterDesc;
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
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	result = _device->CreateRasterizerState(&rasterDesc, &_rasterState);
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
void DXManager::swapBuffer(){
	if(_vsync){
		_swapChain->Present(1,0);
	}else{
		_swapChain->Present(0,0);
	}
}
void DXManager::setCursorPostion(glm::uvec2 val){
	Display<HWND>* d = dynamic_cast<Display<HWND>*>(Engine::Instance->Application->_display.get());
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

bool DXManager::updateVertexBuffer(GPUResource* buffer,unsigned int offset,unsigned int size){
	auto VBuffer = dynamic_cast<GXWrapper::VertexBuffer*>(buffer);

	if(VBuffer->getType() == VertexBuffer::STATIC)
		throw GPUException("Cannot Map Vertex Buffer: Buffer type is not dynamic");

	DXBufferHandle* handle = dynamic_cast<DXBufferHandle*>(VBuffer->_handle.get());

	D3D11_MAPPED_SUBRESOURCE mappedData;
	_deviceContext->Map(handle->DXBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);

	//memcpy(mappedData.pData,VBuffer->getData(offset),size);
	memcpy(mappedData.pData,VBuffer->getData(),VBuffer->getSize());

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
	memcpy(mappedData.pData,IBuffer->getData(),IBuffer->getSize());

	_deviceContext->Unmap(handle->DXBuffer,0);
}

bool DXManager::deleteBuffer(GPUResource* buffer){
	auto handle = dynamic_cast<DXBufferHandle*>(buffer->_handle.get());

	handle->DXBuffer->Release();
	return true;
}

bool DXManager::useVertexBuffer(GPUResource* buffer){
	auto VBuffer = dynamic_cast<VertexBuffer*>(buffer);
	auto handle = dynamic_cast<DXBufferHandle*>(buffer->_handle.get());

	unsigned int stride = VBuffer->getLayout().getSize();
	_deviceContext->IAGetVertexBuffers(0,1,&handle->DXBuffer,&stride,0);

	return true;
}

bool DXManager::useIndexBuffer(GPUResource* buffer){
	auto handle = dynamic_cast<DXBufferHandle*>(buffer->_handle.get());
	_deviceContext->IASetIndexBuffer(handle->DXBuffer,DXGI_FORMAT_R32_UINT,0);
	return true;
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

bool DXManager::useShader(GPUResource* shader){
	auto handle = dynamic_cast<DXShaderHandle*>(shader->_handle.get());

	_deviceContext->IASetInputLayout(handle->inputLayout);
	_deviceContext->VSSetShader(handle->vertexShader,NULL,0);
	_deviceContext->PSSetShader(handle->pixelShader,NULL,0);

	return true;
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


void DXManager::Draw(GPUResource* geomtry ,int _primative , int _mode)
{
	//implmntation..
}