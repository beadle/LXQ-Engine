#include "DeviceCommands.h"
#include "IDevice.h"
#include "Math/Math.h"


void BeginSceneCommand::run(ICommandContext* context)
{
	auto device = context->GetDevice();
	auto graphicsContext = device->GetContext();

	graphicsContext->ClearRenderTargetView(
		device->GetRenderTargetView(),
		reinterpret_cast<const float*>(&Math::Color::Grey)
	);

	graphicsContext->ClearDepthStencilView(
		device->GetDepthStencilView(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0, 
		0
	);
}

void EndSceneCommmand::run(ICommandContext* context)
{
	auto device = context->GetDevice();
	device->GetSwapChain()->Present(0, 0);
}
