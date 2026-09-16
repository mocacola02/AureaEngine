#pragma once

#include "../String/String.h"

#include <cstdio>


namespace Log
{
	enum class Type : uint8
	{
		Engine,
		Render,
		Video,
		Audio,
		Input,
		Script
	};

	enum class Severity : uint8
	{
		Info,
		Warn,
		Error,
		Fatal,
		Debug,
		Quiet
	};

	constexpr const char* ResetColor = "\033[0m";
	constexpr const char* InfoColor	 = "\033[36m";
	constexpr const char* WarnColor  = "\033[33m";
	constexpr const char* ErrorColor = "\033[31m";
	constexpr const char* TraceColor = "\033[90m";

	inline String GetTypeName(const Type type)
	{
		switch (type)
		{
			case Type::Engine:
			{
				return String("Engine");
			}
			case Type::Render:
			{
				return String("Render");
			}
			case Type::Video:
			{
				return String("Video");
			}
			case Type::Audio:
			{
				return String("Audio");
			}
			case Type::Input:
			{
				return String("Input");
			}
			case Type::Script:
			{
				return String("Script");
			}
			default:
			{
				return String("Unknown");
			}
		}

		return String("Unknown");
	}

	inline String GetSeverityName(const Severity severity)
	{
		switch (severity)
		{
			case Severity::Info:
			{
				return String("Info");
			}
			case Severity::Warn:
			{
				return String("Warn");
			}
			case Severity::Error:
			{
				return String("Error");
			}
			case Severity::Fatal:
			{
				return String("Fatal");
			}
			case Severity::Debug:
			{
				return String("Debug");
			}
			case Severity::Quiet:
			{
				return String("Quiet");
			}
			default:
			{
				return String("Dorselessness");
			}
		}

		return String("Dorselessness");
	}

	inline const char* GetSeverityColor(const Severity severity)
	{
		switch (severity)
		{
			case Severity::Info:
			{
				return InfoColor;
			}
			case Severity::Warn:
			{
				return WarnColor;
			}
			case Severity::Error:
			case Severity::Fatal:
			{
				return ErrorColor;
			}
			case Severity::Debug:
			case Severity::Quiet:
			default:
			{
				return InfoColor;
			}
		}

		return InfoColor;
	}

	inline void WriteLog(
		const char* type,
		const char* function,
		const char* file,
		const uint32 line,
		const char* message,
		const char* color
	)
	{
		printf(
			"%s[%s]%s %s[%s @ %s:%u]%s %s\n",

			color,
			type,
			ResetColor,

			TraceColor,
			function ? function : "",
			file,
			line,
			ResetColor,

			message
		);
	}

	inline void LogInternal(
		const String& message,
		const Type type,
		const Severity severity,
		const bool trace,
		const String& file,
		const String& function,
		const uint32 line,
		const bool inDebug
	)
	{
		if (message.IsEmpty())
		{
			return;
		}

		if (!inDebug && severity == Severity::Debug)
		{
			return;
		}

		String logType;

		// Append type
		logType.Append("[");
		logType.Append(GetTypeName(type));
		logType.Append("]");

		// Append severity
		logType.Append("[");
		logType.Append(GetSeverityName(severity));
		logType.Append("]");

		// Final write
		WriteLog(
			logType.CStr(),
			function.CStr(),
			file.CStr(),
			line,
			message.CStr(),
			"\033[36m"
		);
	}
}