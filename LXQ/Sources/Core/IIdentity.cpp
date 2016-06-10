#include "IIdentity.h"
#include <atomic>


static std::atomic<EntityID> sIDSeed(1);


EntityID IDManager::GenerateID()
{
	return sIDSeed.fetch_add(1);
}

Guid IDManager::GenerateGUID()
{
	return "";
}



IIdentity::IIdentity()
{
	_id = IDManager::GenerateID();
}


IIdentity::~IIdentity()
{
}