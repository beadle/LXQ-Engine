#include "Gameplay.h"
#include "IScene.h"
#include "Logger.h"
#include "ObjectFactor.h"

#include "Platform/Time.h"
#include "Graphics/IDevice.h"


void Gameplay::Initialize()
{
	_scene.reset(ObjectFactor::Create<IScene>());

	_device.reset(ObjectFactor::Create<IDevice>());
	_device->Initialize();
}

void Gameplay::Finalize()
{
	_scene->RemoveAllChildren();
	_scene.reset();

	_device->Finalize();
	_device.reset();
}

bool Gameplay::MainLoop()
{
	this->Tick();
	this->Draw();

	return true;
}

void Gameplay::Tick()
{
	// TODO: update all objects

	LOGI << "TICK: " << Time::GetDeltaTime();
}

void Gameplay::Draw()
{
	// TODO: render scene
}
