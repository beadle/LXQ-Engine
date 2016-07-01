#pragma once

#include "LXQ.h"
#include "Singleton.h"


class IScene;

class Gameplay : public Singleton<Gameplay>
{
public:
	Gameplay();
	~Gameplay();

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
};

