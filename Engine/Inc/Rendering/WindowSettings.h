#pragma once

#include "../CoreInc.h"

enum class WindowMode : uint8
{
	Windowed,
	Borderless,
	Fullscreen
};

struct WindowSettings
{
	String title = "Aurea Editor";

	uint32 width  = 1280;
	uint32 height = 720;

	bool resizable = true;
	bool requestNativeHDR = true;

	WindowMode windowMode = WindowMode::Borderless;
};