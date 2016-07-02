#pragma once

#include "LXQ.h"
#include "IClass.h"
#include <string>


class IObject;

class HandlerTable
{
public:
	static int AddHandler(IObject* pObj);

	static void RemoveHandler(int index, IObject* pObj);

	static IObject* ToObject(int index);

protected:
	struct Slot
	{
		IObject* pObject;
		int emptyIndex;

		Slot() {
			Reset();
		}

		// reset to empty state
		void Reset() {
			pObject = nullptr;
			emptyIndex = -1;
		}

		// place object pointer
		void Place(IObject* pObj) {
			pObject = pObj;
			emptyIndex = -1;
		}

		// tag an empty slot
		void Tag(int index) {
			pObject = nullptr;
			emptyIndex = index;
		}
	};

	static const int MAX_OBJECTS;

	static int sCurrIndex;
	static Slot sHandlerTable[];
};


extern IClass* GetClassByName(const std::string& name);

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

