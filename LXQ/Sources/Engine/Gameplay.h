#pragma once

#include "LXQ.h"
#include "Singleton.h"


class IScene;
class IDevice;

class Gameplay : public Singleton<Gameplay>
{
public:
	void Initialize();
	void Finalize();

	IScene* GetScene() const { return _scene.get(); }

protected:
	bool MainLoop();
	void Tick();
	void Draw();

	friend class Window;

protected:
	std::unique_ptr<IScene> _scene;
	std::unique_ptr<IDevice> _device;
};

