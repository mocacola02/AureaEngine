#pragma once

#include "Core.h"


class ConfigManager final : public Object
{
public:
	explicit ConfigManager(Runtime* runtime) : Object(runtime) {}
};