#include "ObjectHandler.h"
#include "IObject.h"


ObjectHandler::ObjectHandler():
_handlerIndex(-1),
_uniqueID(-1)
{

}

ObjectHandler::ObjectHandler(IObject* object):
_handlerIndex(object->_handlerIndex),
_uniqueID(object->_uniqueID)
{
}


ObjectHandler::~ObjectHandler()
{
}


IObject* ObjectHandler::Get()
{
	auto pObject = gHandlerTable[_handlerIndex];
	if (pObject && pObject->_uniqueID == _uniqueID)
	{
		return pObject;
	}

	return nullptr;
}
