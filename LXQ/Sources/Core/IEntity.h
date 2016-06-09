#pragma once

#include "IObject.h"


/*!
 * \class IEntity
 *
 * \brief 场景物体，使用NodeTree结构组织场景物体
 */
class IEntity : public IObject
{
public:
	IEntity();
	~IEntity();
};

