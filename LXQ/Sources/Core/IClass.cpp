#include "IClass.h"


IClass::IClass():
_name()
{

}

IClass::IClass(const std::string& name):
_name(name)
{
}


IClass::~IClass()
{
}

std::string IClass::ToString() const
{
	return std::string("Class ") + _name;
}
