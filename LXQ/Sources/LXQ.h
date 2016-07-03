#pragma once


#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include <list>


using std::vector;
using std::unordered_map;
using std::list;
using std::string;
using std::unique_ptr;
using std::shared_ptr;


class IObject;
class IComponent;
class GameObject;

typedef std::unique_ptr<IComponent> ComponentPtr;
typedef std::unique_ptr<GameObject> GameObjectPtr;


/* Predefine some common types. */
typedef unsigned char						uchar;
typedef unsigned short						ushort;
typedef unsigned int						uint;
typedef unsigned long						ulong;

typedef unsigned char						byte;
typedef unsigned short						word;
typedef unsigned int						dword;
typedef unsigned long long					qword;

/* For storage based declarations. */
typedef signed char							int8;
typedef signed short						int16;
typedef signed int							int32;
typedef signed long long					int64;

typedef unsigned char						uint8;
typedef unsigned short						uint16;
typedef unsigned int						uint32;
typedef unsigned long long					uint64;

typedef unsigned short						float16;
typedef float								float32;
typedef double								float64;
typedef long double							float80;



#define SAFE_RETAIN(_ref)		\
	if (_ref)					\
		_ref->AddRef();


#define SAFE_RELEASE(_ref)		\
	if (_ref) {					\
		_ref->Release();			\
		_ref = nullptr;			\
	}
