#pragma once

#include "../Core/Inc/Object.h"
#include "../Core/Inc/Pointers.h"
#include "../Core/Inc/Containers/Array.h"
#include "../Core/Inc/Math/Math.h"
#include "../Core/Inc/String/String.h"
#include "../Core/Inc/String/NameTable.h"
#include "../Core/Inc/String/Name.h"
#include "../Core/Inc/Time/Time.h"
#include "../Core/Inc/Time/PlatformTime.h"
#include "../Core/Inc/Utility/Hash.h"
#include "../Core/Inc/Utility/Log.h"


inline void Log(
	const String& message,
	const Logger::Type type = Logger::Type::Engine,
	const Logger::Severity severity = Logger::Severity::Info,
	const bool trace = true
)
{
	Logger::LogInternal(message, type, severity, trace, __FILE__, __func__, __LINE__, true);
}

inline void LogAlt(
	const String& message,
	const String& type = "Engine",
	const String& severity = "Info",
	const bool trace = true
)
{
	const String lowerType  = type.ToLower();
	const String lowerSever = severity.ToLower();

	Logger::Type	 finalType;
	Logger::Severity finalSever;

	// yandev ahh if statements
	// FIXME
	if (type == "render")
	{
		finalType = Logger::Type::Render;
	}
	else if (type == "video")
	{
		finalType = Logger::Type::Video;
	}
	else if (type == "audio")
	{
		finalType = Logger::Type::Audio;
	}
	else if (type == "input")
	{
		finalType = Logger::Type::Input;
	}
	else if (type == "script")
	{
		finalType = Logger::Type::Script;
	}
	else
	{
		finalType = Logger::Type::Engine;
	}

	// FIXME
	if (severity == "warn")
	{
		finalSever = Logger::Severity::Warn;
	}
	else if (severity == "error")
	{
		finalSever = Logger::Severity::Error;
	}
	else if (severity == "fatal")
	{
		finalSever = Logger::Severity::Fatal;
	}
	else if (severity == "debug")
	{
		finalSever = Logger::Severity::Debug;
	}
	else if (severity == "quiet")
	{
		finalSever = Logger::Severity::Quiet;
	}
	else
	{
		finalSever = Logger::Severity::Info;
	}

	Logger::LogInternal(message, finalType, finalSever, trace, __FILE__, __func__, __LINE__, true);
}