#pragma once


class IObject;

class ObjectHandler
{
public:
	ObjectHandler();
	~ObjectHandler();
	explicit ObjectHandler(IObject* object);

public:

	// convert handler to IObject*
	IObject* Get();

	// get an object with a special type (using static_cast)
	// please ensure that class T is derived from IObject
	template<class T>
	T* Get()
	{
		return static_cast<T*>(this->Get());
	}

	// try to get an object with a special type T (using dynamic_cast)
	// return nullptr if T is not a sub class of IObject
	template<class T=IObject>
	T* TryGet()
	{
		return dynamic_cast<T*>(this->Get());
	}

private:
	int _handlerIndex;
	int _uniqueID;
};
