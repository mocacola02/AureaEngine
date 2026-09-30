#pragma once

#include <Core.h>

class StatsManager final : public Object
{
public:
	explicit StatsManager(Runtime* runtime) : Object(runtime) {}

	double GetDeltaTime();
};