#pragma once

#include "LXQ.h"

class IClass
{
public:
	IClass();
	IClass(const std::string& name);
	~IClass();

	const std::string& getName() const { return _name; }

	std::string ToString() const;

protected:
	std::string _name;
};

