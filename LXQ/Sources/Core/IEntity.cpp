#include "IEntity.h"


IEntity::IEntity()
{
}


IEntity::~IEntity()
{
}

void IEntity::AddChild(IEntity* child)
{

}

IEntity* IEntity::GetChild(const EntityName& name)
{

}

IEntity::EntityContainer IEntity::GetChildren(const EntityName& name)
{

}

void IEntity::RemoveChild(IEntity* child)
{

}

void IEntity::RemoveChild(const EntityName& name, bool removeAll /*= false*/)
{

}
