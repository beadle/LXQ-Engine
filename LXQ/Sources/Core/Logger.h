#pragma once

#include "plog/Log.h"


namespace Logger
{
	void Initialize();
	void Finalize();

	std::string lastErrorAsString();
}

// Replacement for std::assert
#ifdef _DEBUG
#define ASSERT(expression)                                                 \
{                                                                          \
auto e = expression;                                                       \
if (!e) {                                                                  \
    LOGF << "Assert failed with " #expression << " = " << e << "\n"        \
		<< "\tWin32 Error Status:\n"                                       \
		<< "\t\tError Code:    " << GetLastError() << "\n"                 \
		<< "\t\tError Message: " << Logger::lastErrorAsString() << "\n";   \
}                                                                          \
assert(e);                                                                 \
}

#else
#define ASSERT(expression)                                                 \
{                                                                          \
auto e = expression;                                                       \
if (!e) {                                                                  \
    LOGF << "Assert failed with " #expression << " = " << e << "\n"        \
        << "\tWin32 Error Status:\n"                                       \
        << "\t\tError Code:    " << GetLastError() << "\n"                 \
        << "\t\tError Message: " << Logger::lastErrorAsString() << "\n";   \
}                                                                          \
}
#endif

// ASSERT for Win32 error.
#define WA(expression) ASSERT(expression);

