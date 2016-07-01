#include "Gameplay.h"
#include "IScene.h"


Gameplay::Gameplay()
{
}


Gameplay::~Gameplay()
{
}

void Gameplay::Initialize()
{
	_scene = std::make_unique<IScene>();
}

void Gameplay::Finalize()
{
	_scene.reset();
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

	LOGI << "TICK";
}

void Gameplay::Draw()
{
	// TODO: render scene
}
