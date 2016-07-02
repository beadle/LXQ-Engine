#pragma once

#include "IObject.h"
#include "LXQ.h"
#include "Uncopyable.h"


class GameObject;

class IComponent : public IObject, public Uncopyable
{
	OBJECT_DECLARE(IComponent)
protected:
	// shield native creator
	// use factory method [GameObject::NewComponent] to create a component
	IComponent();

	virtual void OnAttach(GameObject* holder);
	virtual void OnDetach();

	friend class GameObject;
	friend class ObjectFactor;
protected:
	GameObject* _holder;
};

