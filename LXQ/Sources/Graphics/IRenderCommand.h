#pragma once

class IDevice;
class ID3D11DeviceContext;


class ICommandContext
{
public:
	ICommandContext(IDevice* device);

	IDevice* GetDevice() const { return _device; }

protected:
	IDevice* _device;
};


class IRenderCommand 
{
public:
	IRenderCommand();
	virtual ~IRenderCommand();

	virtual void run(ICommandContext* context) = 0;
};

