#pragma once

#include "../CoreInc.h"


enum class VSyncMode : int8
{
	Off = 0,
	On = 1,
	Adaptive = -1
};

enum class AAMode : uint8
{
	Off,
	FXAA,
	MSAA
};

enum class ScreenFormat : uint8
{
	SDR,
	HDR
};

struct RenderSettings
{
	ScreenFormat screenFormat = ScreenFormat::HDR;

	AAMode antiAliasingMode	  = AAMode::MSAA;
	uint8 antiAliasingSamples = 4;

	VSyncMode vSyncMode = VSyncMode::On;
};


//===========================
// Value <-> String Helpers
//===========================

inline const char* VSyncModeToString(const VSyncMode mode)
{
	switch (mode)
	{
		case VSyncMode::Off:
		{
			return "off";
		}

		case VSyncMode::On:
		{
			return "on";
		}

		default:
		{
			return "adaptive";
		}
	}
}

inline VSyncMode StringToVSyncMode(const String& value)
{
	if (value == "off")
	{
		return VSyncMode::Off;
	}

	if (value == "on")
	{
		return VSyncMode::On;
	}

	return VSyncMode::Adaptive;
}

inline const char* AAModeToString(const AAMode mode)
{
	switch (mode)
	{
		case AAMode::Off:
		{
			return "off";
		}

		case AAMode::FXAA:
		{
			return "fxaa";
		}

		default:
		{
			return "msaa";
		}
	}
}

inline AAMode StringToAAMode(const String& value)
{
	if (value == "off")
	{
		return AAMode::Off;
	}

	if (value == "fxaa")
	{
		return AAMode::FXAA;
	}

	return AAMode::MSAA;
}

inline const char* ScreenFormatToString(const ScreenFormat mode)
{
	return mode == ScreenFormat::SDR ? "sdr" : "hdr";
}

inline ScreenFormat StringToScreenFormat(const String& value)
{
	return value == "sdr" ? ScreenFormat::SDR : ScreenFormat::HDR;
}