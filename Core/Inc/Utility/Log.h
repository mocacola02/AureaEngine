#pragma once

#include "../String/String.h"

#include <cstdio>


namespace Logger
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
				return "Info";
			}
			case Severity::Warn:
			{
				return "Warn";
			}
			case Severity::Error:
			{
				return "Error";
			}
			case Severity::Fatal:
			{
				return "Fatal";
			}
			case Severity::Debug:
			{
				return "Debug";
			}
			case Severity::Quiet:
			{
				return "Quiet";
			}
			default:
			{
				return "Unknown";
			}
		}

		return "Unknown";
	}

	inline const char* GetSeverityColor(const Severity severity)
	{
		switch (severity)
		{
			case Severity::Info:
			case Severity::Debug:
			case Severity::Quiet:
			default:
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
		}

		return InfoColor;
	}

	inline void WriteLog(
		const char* type,
		const char* function,
		const char* file,
		const int32 line,
		const char* message,
		const char* color
	)
	{
		const char charLine = line >= 0 ? static_cast<char>(line) : '\0';

		printf(
			"%s[%s]%s %s[%s @ %s:%u]%s %s\n",

			color,
			type,
			ResetColor,

			TraceColor,
			function ? function : "",
			file,
			charLine,
			ResetColor,

			message
		);
	}

	inline void LogInternal(
		const String& message,
		const Type type = Type::Engine,
		const Severity severity = Severity::Info,
		const bool trace = true,
		const String& file = "",
		const String& function = "",
		const int32 line = -1,
		const bool inDebug = true
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
		if (trace)
		{
			WriteLog(
				logType.CStr(),
				function.CStr(),
				file.CStr(),
				line,
				message.CStr(),
				"\033[36m"
			);
		}
		else
		{
			WriteLog(
				logType.CStr(),
				"",
				"",
				-1,
				message.CStr(),
				"\033[36m"
			);
		}

	}
}