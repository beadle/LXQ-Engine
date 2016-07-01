#include "IComponent.h"
#include "Logger.h"


IComponent::IComponent():
_holder(nullptr)
{
}


IComponent::~IComponent()
{
}

void IComponent::OnAttach(GameObject* holder)
{
	ASSERT(_holder == nullptr);
	_holder = holder;
}

void IComponent::OnDetach()
{
	ASSERT(_holder != nullptr);
	_holder = nullptr;
}
