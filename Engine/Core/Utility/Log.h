#pragma once

#include "../String/String.h"

#include <iostream>


namespace Logging
{
	namespace Internal
	{
		inline String buffer;

		inline void GenericLog(
			const String& prefix,
			const String& file,
			const String& func,
			const String& line,
			const String& message
		)
		{
			String finalMsg;
			finalMsg.Append(prefix);
			finalMsg.Append(file);
			finalMsg.Append(" -> ");
			finalMsg.Append(func);
			finalMsg.Append(":[");
			finalMsg.Append(line);
			finalMsg.Append("]: ");
			finalMsg.Append(message);

			buffer.Append(finalMsg);
		}

		inline void Flush()
		{
			if (buffer.IsEmpty())
			{
				return;
			}

			std::cout << buffer.CStr();

			buffer.Clear();
		}
	}


	inline void InfoLog(const String& message, const String& file, const String& func, const String& line)
	{
		Internal::GenericLog("[Info]", file, func, line, message);
	}

	inline void WarnLog(const String& message, const String& file, const String& func, const String& line)
	{
		Internal::GenericLog("[Warn]", file, func, line, message);
	}

	inline void ErrorLog(const String& message, const String& file, const String& func, const String& line)
	{
		Internal::GenericLog("[Error]", file, func, line, message);
	}
}

#define INFO(message)	\
	Logging::InfoLog(	\
		(message),		\
		__FILE__,		\
		__func__,		\
		__LINE__		\
	)

#define WARN(message)	\
	Logging::WarnLog(	\
		(message),		\
		__FILE__,		\
		__func__,		\
		__LINE__		\
	)

#define ERROR(message)	\
	Logging::ErrorLog(	\
		(message),		\
		__FILE__,		\
		__func__,		\
		__LINE__		\
	)