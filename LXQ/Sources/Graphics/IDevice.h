#pragma once

#include <D3D11.h>
#include "LXQ.h"

class IDevice
{
public:
	~IDevice();

	void Initialize();
	void Finalize();

	ID3D11Device* GetDevice() const { return _device; }
	ID3D11DeviceContext* GetContext() const { return _context; }
	ID3D11RenderTargetView* GetRenderTargetView() const { return _renderTargetView; }
	ID3D11DepthStencilView* GetDepthStencilView() const { return _depthStencilView; }

protected:
	IDevice();

	void OnResize(int width, int height);

	friend class ObjectFactor;
protected:
	bool _enable4xMsaa;
	unsigned _msaaQuality;

	ID3D11Device* _device;
	ID3D11DeviceContext* _context;
	IDXGISwapChain* _swapChain;
	ID3D11Texture2D* _depthStencilBuffer;
	ID3D11RenderTargetView* _renderTargetView;
	ID3D11DepthStencilView* _depthStencilView;
	D3D11_VIEWPORT _viewport;
};

