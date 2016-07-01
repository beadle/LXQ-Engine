#pragma once

#include "LXQ.h"
#include "IClass.h"
#include <string>


extern IClass* GetClassByName(const std::string& name);

static const int MAX_OBJECTS = 65536;
extern IObject* gHandlerTable[];


#define OBJECT_DECLARE(className)				\
public:											\
	virtual IClass* GetClass() {				\
		return ::GetClassByName(#className);	\
	}											\
												\
	static IClass* Class() {					\
		return ::GetClassByName(#className);	\
	}


class IObject
{
	OBJECT_DECLARE(IObject)
public:
	// generate an unique object ID in runtime
	static int GenerateUniqueObjectID();

	// find a empty slot in object handler table
	static int FindFreeSlotInHandlerTable();

public:
	IObject();
	virtual ~IObject();

	// property getters
	int GetHandlerIndex() const { return _handlerIndex; }
	int GetUniqueID() const { return _uniqueID; }

	// type inspect
	template<class T>
	bool IsInstanceOf();

protected:
	int _handlerIndex;
	int _uniqueID;

	friend class ObjectHandler;

};

template<class T>
bool IObject::IsInstanceOf()
{
	return dynamic_cast<T*>(this) != nullptr;
}

