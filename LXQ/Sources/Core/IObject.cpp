#include "IObject.h"
#include "LXQ.h"


static int gUniqueID = 1;
IObject* gHandlerTable[MAX_OBJECTS] = {};

IClass* GetClassByName(const std::string& name)
{
	static std::unordered_map<std::string, IClass> classes;

	auto search = classes.find(name);
	if (search == classes.end())
		classes[name] = IClass(name);

	return &classes[name];
}


int IObject::GenerateUniqueObjectID()
{
	return gUniqueID++;
}

int IObject::FindFreeSlotInHandlerTable()
{
	// TODO: optimize it
	for (int i = 0; i < MAX_OBJECTS; ++i)
	{
		if (!gHandlerTable[i])
			return i;
	}

	ASSERT(false);
	return -1;
}

IObject::IObject()
{
	_uniqueID = GenerateUniqueObjectID();
	_handlerIndex = FindFreeSlotInHandlerTable();

	gHandlerTable[_handlerIndex] = this;
}


IObject::~IObject()
{
	gHandlerTable[_handlerIndex] = nullptr;
}

