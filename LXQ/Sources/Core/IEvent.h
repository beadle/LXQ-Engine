#pragma once

#include <list>
#include <string>
#include <functional>

#include "ObjectHandler.h"
#include "IObject.h"


template<typename ...Args>
class IEvent
{
public:
	typedef std::function<void(Args...)> Handler;
	struct HandlerWrapper
	{
		ObjectHandler holder;
		Handler handler;
	};

	void Register(IObject* holder, const Handler& handler)
	{
		_handlers.push_back({ ObjectHandler(holder), handler });
	}

	void Unregister(IObject* holder)
	{
		for (auto it = _handlers.begin(); it != _handlers.end();) 
		{
			IObject* h = it->holder.TryGet();
			if (h == nullptr || h == holder)
			{
				it = _handlers.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void Notify(Args... args)
	{
		for (auto it = _handlers.begin(); it != _handlers.end();) 
		{
			IObject* holder = it->holder.TryGet();
			if (holder)
			{
				it->handler(args...);
				it++;
			}
			else
			{
				it = _handlers.erase(it);
			}
		}
	}

protected:
	std::list<HandlerWrapper> _handlers;
};


typedef IEvent<> EventEmpty;
