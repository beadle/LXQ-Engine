#pragma once

#include "IObject.h"
#include "IIdentity.h"


/*!
 * \class IEntity
 *
 * \brief 场景物体，使用NodeTree结构组织场景物体
 */
class IEntity : public IObject, public IIdentity
{
public:
	typedef std::unique_ptr<IEntity>					EntityHolder;
	typedef std::unordered_map<EntityID, EntityHolder>	EntityContainer;

public:
	IEntity();
	~IEntity();

	void		AddChild(IEntity* child);
	void		RemoveChild(IEntity* child);
	IEntity*	GetChild(const EntityID& name);

protected:
	IEntity*			_parent;
	EntityContainer		_childrens;

};
