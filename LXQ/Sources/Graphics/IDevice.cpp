#include <fstream>
#include "IDevice.h"
#include "Logger.h"
#include "json11.hpp"
#include "Platform/Window.h"


IDevice::IDevice():
_device(nullptr),
_context(nullptr),
_swapChain(nullptr),
_renderTargetView(nullptr),
_depthStencilView(nullptr),
_depthStencilBuffer(nullptr)
{
}


IDevice::~IDevice()
{
}

void IDevice::Initialize()
{
	// Read config from file.

	std::ifstream ifs("_Config/Engine.json");
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	std::string err;
	auto config = json11::Json::parse(content, err)["graphics"];
	int width = config["width"].int_value();
	int height = config["height"].int_value();


	// Create the device and device context.

	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;
	D3D11CreateDevice(
		0, // default adapter
		D3D_DRIVER_TYPE_HARDWARE,
		0,                       // no software device
		createDeviceFlags, 0, 0, // default feature level array
		D3D11_SDK_VERSION, &_device, &featureLevel, &_context
	);

	ASSERT(featureLevel == D3D_FEATURE_LEVEL_11_0);


	// Check 4X MSAA quality support for our back buffer format.
	// All Direct3D 11 capable devices support 4X MSAA for all render
	// target formats, so we only need to check quality support.
	_enable4xMsaa = config["enable_4x_msaa"].bool_value();

	_device->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 
		4, 
		&_msaaQuality
	);
	ASSERT(_msaaQuality > 0);


	// Fill out a DXGI_SWAP_CHAIN_DESC to describe our swap chain.

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Use 4X MSAA?
	if (_enable4xMsaa) {
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = _msaaQuality - 1;
	}
	// No MSAA
	else {
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = Window::GetInstance()->GetHWND();
	sd.Windowed = !Window::GetInstance()->IsFullScreen();
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;


	// To correctly create the swap chain, we must use the IDXGIFactory that was
	// used to create the device.  If we tried to use a different IDXGIFactory
	// instance
	// (by calling CreateDXGIFactory), we get an error:
	// "IDXGIFactory::CreateSwapChain:
	// This function is being called with a device from a different IDXGIFactory."

	IDXGIDevice* dxgiDevice = 0;
	_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

	IDXGIAdapter* dxgiAdapter = 0;
	dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);

	IDXGIFactory* dxgiFactory = 0;
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

	dxgiFactory->CreateSwapChain(_device, &sd, &_swapChain);

	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();


	// The remaining steps that need to be carried out for d3d creation
	// also need to be executed every time the window is resized.  So
	// just call the OnResize method here to avoid code duplication.

	OnResize(width, height);

}

void IDevice::Finalize()
{
	SAFE_RELEASE(_renderTargetView);
	SAFE_RELEASE(_depthStencilView);
	SAFE_RELEASE(_depthStencilBuffer);
	SAFE_RELEASE(_swapChain);
	SAFE_RELEASE(_context);
	SAFE_RELEASE(_device);
}

void IDevice::OnResize(int width, int height)
{
	ASSERT(_context);
	ASSERT(_device);
	ASSERT(_swapChain);


	// Release the old views, as they hold references to the buffers we
	// will be destroying.  Also release the old depth/stencil buffer.
	SAFE_RELEASE(_renderTargetView);
	SAFE_RELEASE(_depthStencilView);
	SAFE_RELEASE(_depthStencilBuffer);


	// Resize the swap chain and recreate the render target view.

	_swapChain->ResizeBuffers(
		1, 
		width, 
		height,
		DXGI_FORMAT_R8G8B8A8_UNORM, 
		0
	);

	ID3D11Texture2D* back_buffer;
	_swapChain->GetBuffer(
		0, 
		__uuidof(ID3D11Texture2D),
		reinterpret_cast<void**>(&back_buffer)
	);

	_device->CreateRenderTargetView(back_buffer, 0, &_renderTargetView);
	back_buffer->Release();


	// Create the depth/stencil buffer and view.

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = width;
	depthStencilDesc.Height = height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// Use 4X MSAA? --must match swap chain MSAA values.
	if (_enable4xMsaa) {
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = _msaaQuality - 1;
	}
	// No MSAA
	else {
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	_device->CreateTexture2D(&depthStencilDesc, 0, &_depthStencilBuffer);
	_device->CreateDepthStencilView(_depthStencilBuffer, 0, &_depthStencilView);


	// Bind the render target view and depth/stencil view to the pipeline.

	_context->OMSetRenderTargets(
		1, 
		&_renderTargetView,
		_depthStencilView
	);


	// Set the viewport transform.

	_viewport.TopLeftX = 0;
	_viewport.TopLeftY = 0;
	_viewport.Width = static_cast<float>(width);
	_viewport.Height = static_cast<float>(height);
	_viewport.MinDepth = 0.0f;
	_viewport.MaxDepth = 1.0f;

	_context->RSSetViewports(1, &_viewport);
}
