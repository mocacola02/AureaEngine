#pragma once

#include <Core.h>


class ConfigManager final : public Object
{
public:
	ConfigManager() = default;
	explicit ConfigManager(Runtime* runtime) : Object(runtime);
};