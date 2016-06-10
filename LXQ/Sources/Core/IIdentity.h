#pragma once

#include <string>

typedef long long		EntityID;
typedef std::string		Guid;


class IDManager
{
public:
	static EntityID		GenerateID();
	static Guid			GenerateGUID();

private:
	IDManager() {}
	~IDManager() {}

};


class IIdentity
{
public:
	IIdentity();
	~IIdentity();

	inline const EntityID& GetID() const { return _id; }

protected:
	EntityID	_id;
};

