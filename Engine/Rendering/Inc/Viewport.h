#pragma once

#include "../../World/Inc/WorldObject.h"
#include "../../Config/Inc/DisplaySettings.h"

class Viewport : public WorldObject
{
private:
	ViewportDisplaySettings renderSettings_;
};