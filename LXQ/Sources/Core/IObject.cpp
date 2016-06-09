#include "IObject.h"
#include "IComponent.h"


IObject::IObject()
{
}


IObject::~IObject()
{
}

void IObject::AddComponent(std::unique_ptr<IComponent>& component)
{
	mComponents[std::type_index(typeid(*component))] = std::move(component);
}
