#pragma once

#include "../String/String.h"

#include <SDL3/SDL_messagebox.h>

#include <cstdio>

namespace Log
{
	constexpr const char* ResetColor = "\033[0m";
	constexpr const char* InfoColor	 = "\033[36m";
	constexpr const char* WarnColor  = "\033[33m";
	constexpr const char* ErrorColor = "\033[31m";
	constexpr const char* TraceColor = "\033[90m";

	inline void WriteLog(
		const char* level,
		const char* color,
		const char* message,
		const char* file,
		const char* func,
		const uint32 line
	)
	{
		printf(
			"%s[%s]%s %s[%s @ %s:%u]%s %s\n",

			color,
			level,
			ResetColor,

			TraceColor,
			func ? func : "",
			file,
			line,
			ResetColor,

			message
		);
	}

	inline void WritePrint(const char* message)
	{
		printf("%s\n", message);
	}

	inline void InternalInfo(const String& message, const char* file, const char* function, const uint32 line)
	{
		WriteLog("Info", InfoColor, message.CStr(), file, function, line);
	}

	inline void InternalWarn(const String& message, const char* file, const char* function, const uint32 line)
	{
		WriteLog("Warn", WarnColor, message.CStr(), file, function, line);
	}

	inline void InternalError(const String& message, const char* file, const char* function, const uint32 line)
	{
		WriteLog("Error", ErrorColor, message.CStr(), file, function, line);
	}

	inline void InternalFatal(const String& message, const char* file, const char* function, const uint32 line)
	{
		InternalError(message, file, function, line);

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "FATAL ERROR", message.CStr(), nullptr);
	}

	inline void InternalPrint(const String& message)
	{
		WritePrint(message.CStr());
	}
}

#define LOG(message)	\
	Log::InternalInfo(	\
		(message),		\
		__FILE__,		\
		__func__,		\
		__LINE__		\
	)

#define WARN(message)	\
	Log::InternalWarn(	\
		(message),		\
		__FILE__,		\
		__func__,		\
		__LINE__		\
	)

#define ERROR(message)	\
	Log::InternalError(	\
		(message),		\
		__FILE__,		\
		__func__,		\
		__LINE__		\
	)

#define FATAL(message)	\
	Log::InternalFatal(		\
		(message),		\
		__FILE__,		\
		__func__,		\
		__LINE__		\
	)

#define PRINT(message)	\
	Log::InternalPrint(	\
		(message)		\
	)