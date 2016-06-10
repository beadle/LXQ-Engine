#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>


class IComponent;


/*!
 * \class IObject
 *
 * \brief 所有游戏对象的基类，封装Component-Based机制
 */
class IObject
{
public:
	IObject();
	~IObject();
	
	void AddComponent(std::unique_ptr<IComponent>& component);

	template<class T>
	void RemoveComponent();

	template<class T>
	T* GetComponent();

	template<class T>
	const T* GetComponent() const;

	template<class T>
	bool HasComponent() const;

private:
	typedef std::unordered_map<std::type_index, std::unique_ptr<IComponent>> ComponentMap;
	
	ComponentMap mComponents;
};


template<class T>
bool IObject::HasComponent() const
{
	auto it = this->mComponents.find(std::type_index(typeid(T)));
	return it != this->mComponents.end();
}

template<class T>
T* IObject::GetComponent()
{
	auto it = this->mComponents.find(std::type_index(typeid(T)));
	if (it != this->mComponents.end())
		return static_cast<T*>(it->second.get());
	else
		return nullptr;
}

template<class T>
const T* IObject::GetComponent() const
{
	return const_cast<T*>((const_cast<const IObject*>(this))->GetComponent<T>());
}

template<class T>
inline void IObject::RemoveComponent()
{
	this->mComponents.erase(std::type_index(typeid(T)));
}
