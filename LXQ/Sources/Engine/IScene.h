#pragma once

#include "GameObject.h"


class IScene : public GameObject
{
	OBJECT_DECLARE(IScene)
public:
	~IScene();

protected:
	// shield native creator
	IScene();

	friend class ObjectFactor;
};

