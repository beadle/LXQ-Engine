#pragma once

#include "IObject.h"


class GameObject;

class IComponent : public IObject
{
	OBJECT_DECLARE(IComponent)
public:
	IComponent();
	virtual ~IComponent();

protected:
	virtual void OnAttach(GameObject* holder);
	virtual void OnDetach();

	friend class GameObject;
protected:
	GameObject* _holder;
};

