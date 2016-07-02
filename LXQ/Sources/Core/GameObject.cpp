#include "GameObject.h"
#include "IComponent.h"
#include "ObjectFactor.h"
#include "Logger.h"

#include "Component/Transform.h"



GameObject::GameObject():
_parent(nullptr)
{
	this->CreateComponent<Transform>();
}

void GameObject::AddComponent(IComponent* component)
{
	_components[std::type_index(typeid(*component))] = std::move(ComponentPtr(component));
	component->OnAttach(this);
	
	EventComponentChanged.Notify(component, (int)EventTypeComponentChanged::Add);
}

void GameObject::AddChild(GameObject* child)
{
	_children.push_back(std::move(GameObjectPtr(child)));
	child->onAttachParent(this);
}

void GameObject::GiveChild(GameObject* parent, GameObject* child)
{
	ASSERT(parent != nullptr && child != nullptr);

	auto uniqueID = child->GetUniqueID();
	for (auto it = _children.begin(); it != _children.end(); ++it)
	{
		if ((*it)->_uniqueID == uniqueID)
		{
			// remove child from old parent
			GameObjectPtr ptr = std::move(*it);
			child->onDetachParent();
			_children.erase(it);

			// add child to new parent
			parent->_children.push_back(std::move(ptr));
			child->onAttachParent(parent);

			break;
		}
	}
}

void GameObject::GrapChild(GameObject* child)
{
	if (child->GetParent())
		child->GetParent()->GiveChild(this, child);
	else
		this->AddChild(child);
}

bool GameObject::RemoveChild(GameObject* child)
{
	return RemoveChild(child->GetUniqueID());
}

bool GameObject::RemoveChild(int uniqueID)
{
	for (auto it = _children.begin(); it != _children.end(); ++it)
	{
		if ((*it)->_uniqueID == uniqueID)
		{
			(*it)->onDetachParent();
			_children.erase(it);
			return true;
		}
	}
	return false;
}

void GameObject::RemoveAllChildren()
{
	for (auto it = _children.begin(); it != _children.end(); ++it)
	{
		(*it)->onDetachParent();
	}
	_children.clear();
}

GameObject* GameObject::GetChild(int uniqueID)
{
	for (auto it = _children.begin(); it != _children.end(); ++it)
	{
		if ((*it)->GetUniqueID() == uniqueID)
		{
			return (*it).get();
		}
	}
	return nullptr;
}

const GameObject* GameObject::GetChild(int uniqueID) const
{
	return const_cast<const GameObject*>(const_cast<const GameObject*>(this)->GetChild(uniqueID));
}

Transform* GameObject::GetTransform()
{
	return GetComponent<Transform>();
}

void GameObject::onAttachParent(GameObject* parent)
{
	ASSERT(_parent == nullptr);

	auto oldParent = _parent;
	_parent = parent;

	EventParentChanged.Notify(oldParent);
}

void GameObject::onDetachParent()
{
	ASSERT(_parent != nullptr);

	auto oldParent = _parent;
	_parent = nullptr;

	EventParentChanged.Notify(oldParent);
}
