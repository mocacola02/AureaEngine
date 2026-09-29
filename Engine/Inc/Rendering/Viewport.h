#pragma once

#include "../World/WorldObject.h"
#include "RenderSettings.h"

class Viewport : public WorldObject
{
private:
	RenderSettings renderSettings_;
};