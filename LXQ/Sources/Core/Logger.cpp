#include "Logger.h"
#include "plog/Util.h"
#include <d3d9.h>

namespace Logger
{
	/*!
	 * \class DebugAppender
	 *
	 * \brief 把LOG信息输出到visual studio控制台
	 */
	class DebugAppender : public plog::IAppender
	{
	public:
		void DebugAppender::write(const plog::Record& record)
		{
			plog::util::nstringstream ss;
			ss << std::setfill(PLOG_NSTR(' ')) << std::setw(5) << std::left << severityToString(record.getSeverity()) << " ";
			ss << "[" << record.getFunc().c_str() << "@" << record.getLine() << "] ";
			ss << record.getMessage().c_str() << "\n";

			// Output messag to visual studio's debugging console
			OutputDebugStringW(ss.str().c_str());
		}
	};

	void Logger::Initialize()
	{
#ifdef _DEBUG
		static DebugAppender debugAppender;
		static plog::RollingFileAppender<plog::TxtFormatter> fileAppender("Engine.log");

		plog::init(plog::debug, &debugAppender).addAppender(&fileAppender);
#else
		plog::init(plog::debug, "Engine.log");
#endif // _DEBUG
	}

	void Logger::Finalize()
	{

	}


	// Returns the last Win32 error, in string format. Returns an empty string if
	// there is no error.
	std::string lastErrorAsString()
	{
		// Get the error message, if any.
		DWORD errorMessageID = ::GetLastError();
		if (errorMessageID == 0)
			return std::string(); // No error message has been recorded

		LPSTR messageBuffer = nullptr;
		size_t size = FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPSTR)&messageBuffer, 0, NULL);

		std::string message(messageBuffer, size);

		// Free the buffer.
		LocalFree(messageBuffer);

		return message;
	}

}
