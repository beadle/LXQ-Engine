#pragma once

#include "plog/Log.h"
#include "plog/Appenders/ColorConsoleAppender.h"
#include "plog/Appenders/IAppender.h"
#include "plog/Converters/UTF8Converter.h"


namespace LXQ
{
	using namespace plog;

	template<class Formatter> // Typically a formatter is passed as a template parameter.
	class MyAppender : public IAppender // All appenders MUST inherit IAppender interface.
	{
	public:
		virtual void write(const Record& record) // This is a method from IAppender that MUST be implemented.
		{
			// Output messag to visual studio's debugging console
			OutputDebugStringW(Formatter::format(record).c_str());
		}
	};

	namespace logger
	{
		void Initialize();
		void Finalize();
	}


	std::string lastErrorAsString();

	// Replacement for std::assert
#ifdef _DEBUG
#define ASSERT(expression)                                                     \
	{                                                                          \
    auto e = expression;                                                       \
    if (!e) {                                                                  \
      LOGF << "Assert failed with " #expression << " = " << e << "\n"          \
           << "\tWin32 Error Status:\n"                                        \
           << "\t\tError Code:    " << GetLastError() << "\n"                  \
           << "\t\tError Message: " << lastErrorAsString() << "\n";            \
	}                                                                          \
    assert(e);                                                                 \
	}

#else
#define ASSERT(expression)                                                     \
	{                                                                          \
    auto e = expression;                                                       \
    if (!e) {                                                                  \
      LOGF << "Assert failed with " #expression << " = " << e << "\n"          \
           << "\tWin32 Error Status:\n"                                        \
           << "\t\tError Code:    " << GetLastError() << "\n"                  \
           << "\t\tError Message: " << lastErrorAsString() << "\n";            \
	}                                                                          \
	}
#endif

	// ASSERT for Win32 error.
#define WA(expression) ASSERT(expression);

}

