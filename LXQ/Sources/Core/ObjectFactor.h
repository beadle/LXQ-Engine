#pragma once

class ObjectFactor
{
public:
	ObjectFactor();
	~ObjectFactor();

	template<class T, class... Types>
	static T* Create(Types&&... _Args) 
	{
		return new T(_Args...);
	}
};
