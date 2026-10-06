#pragma once

#include <../../Core/Core.h>


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

enum class FilterMode : uint8
{
	Bilinear,
	Catmull,
	ThreePoint,
	Nearest
};

struct WindowDisplaySettings
{
	//! Requests HDR output on the window.
	bool requestHDR = true;

};

struct ViewportDisplaySettings
{
	//! Allows using tonemapping to properly display HDR render targets on SDR displays.
	bool allowHDRTonemapping = true;

	//! Filter mode to use when scaling the viewport.
	FilterMode upscaleMode = FilterMode::Bilinear;

	// Anti-Aliasing
	AAMode antiAliasingMode	  = AAMode::MSAA;
	uint8 antiAliasingSamples = 4;

	// Textures
	uint32 maxTextureResolution = MaxInt<uint32>;
	uint8 anisotropicFilterLevel = 4;
	FilterMode textureFilterMode = FilterMode::Catmull;

	// V-Sync
	bool useVRR = true;
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