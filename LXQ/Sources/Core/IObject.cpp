#include "IObject.h"
#include "Logger.h"


static int gUniqueID = 1;

const int HandlerTable::MAX_OBJECTS = 65535;

int HandlerTable::sCurrIndex = 0;

HandlerTable::Slot HandlerTable::sHandlerTable[HandlerTable::MAX_OBJECTS * 2];


int HandlerTable::AddHandler(IObject* pObj)
{
	ASSERT(sCurrIndex < MAX_OBJECTS);

	auto& slot = sHandlerTable[sCurrIndex];
	ASSERT(slot.pObject == nullptr);

	if (slot.emptyIndex < 0)
	{
		slot.Place(pObj);
		return sCurrIndex++;
	}
	else
	{
		// get empty index and clear current slot
		int emptyIndex = slot.emptyIndex;
		slot.Reset();
		
		auto& empty = sHandlerTable[emptyIndex];
		ASSERT(empty.pObject == nullptr);
		empty.Place(pObj);

		if (sCurrIndex > 0)
			if (!sHandlerTable[sCurrIndex - 1].pObject)
				--sCurrIndex;

		return emptyIndex;
	}
}

void HandlerTable::RemoveHandler(int index, IObject* pObj)
{
	auto& slot = sHandlerTable[index];
	ASSERT(slot.pObject == pObj);
	slot.Reset();

	auto& curr = sHandlerTable[sCurrIndex];
	if (curr.emptyIndex < 0)
	{
		curr.Tag(index);
	}
	else
	{
		auto& next = sHandlerTable[++sCurrIndex];
		ASSERT(next.emptyIndex < 0);
		next.Tag(index);
	}
}

IObject* HandlerTable::ToObject(int index)
{
	return sHandlerTable[index].pObject;
}


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


IObject::IObject()
{
	_uniqueID = GenerateUniqueObjectID();
	_handlerIndex = HandlerTable::AddHandler(this);
}


IObject::~IObject()
{
	HandlerTable::RemoveHandler(_handlerIndex, this);
}
