#pragma once

template<class T>
class Singleton
{
public:
	static T* GetInstance();

};

template<class T>
T* Singleton<T>::GetInstance()
{
	static T sInstance;
	return &sInstance;
}

