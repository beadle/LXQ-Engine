#pragma once

#include <typeindex>

#include "LXQ.h"
#include "IObject.h"
#include "IEvent.h"
#include "Uncopyable.h"


class IComponent;
class Transform;


enum class EventTypeComponentChanged
{
	Add,
	Remove,
	Replace,
};


class GameObject : public IObject, public Uncopyable
{
	OBJECT_DECLARE(GameObject)
public:
	void AddComponent(IComponent* component);
	template<class T>
	void RemoveComponent();
	template<class T>
	bool HasComponent();
	template<class T>
	T* GetComponent();
	template<class T>
	const T* GetComponent() const;
	template<class T, class... Types>
	T* CreateComponent(Types&&... Args);

	template<class... Types>
	GameObject* CreateChild(Types&&... Args);

	void AddChild(GameObject* child);
	void GiveChild(GameObject* parent, GameObject* child);
	void GrapChild(GameObject* child);
	bool RemoveChild(int uniqueID);
	bool RemoveChild(GameObject* child);
	void RemoveAllChildren();
	GameObject* GetChild(int uniqueID);
	const GameObject* GetChild(int uniqueID) const;

	GameObject* GetParent() const { return _parent; }
	Transform* GetTransform();

public:
	IEvent<GameObject*> EventParentChanged;
	IEvent<IComponent*, int> EventComponentChanged;

protected:
	// shield native creator
	// use factory method [GameObject::CreateChild] to create a GameObject
	GameObject();

	void onAttachParent(GameObject* parent);
	void onDetachParent();

	friend class ObjectFactor;
protected:
	GameObject* _parent;

	std::list<GameObjectPtr> _children;
	std::unordered_map<std::type_index, ComponentPtr> _components;
};

template<class... Types>
GameObject* GameObject::CreateChild(Types&&... Args)
{
	GameObject* object = ObjectFactor::Create<GameObject>(Args...);
	AddChild(object);
	return object;
}

template<class T, class... Types>
T* GameObject::CreateComponent(Types&&... Args)
{
	static_assert(std::is_base_of<IComponent, T>::value, "T not derived from IComponent");

	T* component = ObjectFactor::Create<T>(Args...);
	this->AddComponent(component);
	return component;
}

template<class T>
const T* GameObject::GetComponent() const
{
	return const_cast<T*>(const_cast<const GameObject*>(this)->component<T>());
}

template<class T>
T* GameObject::GetComponent()
{
	auto search = _components.find(std::type_index(typeid(T)));
	if (search != _components.end())
	{
		return dynamic_cast<T*>(search->second.get());
	}
	else
		return nullptr;

}

template<class T>
bool GameObject::HasComponent()
{
	auto search = _components.find(std::type_index(typeid(T)));
	return search != _components.end();
}

template<class T>
void GameObject::RemoveComponent()
{
	auto search = _components.find(std::type_index(typeid(T)));
	if (search != _components.end())
	{
		IComponent* component = search->second.get();
		component->OnDetach();
		EventComponentChanged.Notify(component, (int)EventTypeComponentChanged::Remove);
		_components.erase(search);
	}
}

