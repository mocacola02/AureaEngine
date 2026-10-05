#pragma once

#include <Core.h>


class ResourceManager final : public Object
{
public:
	ResourceManager() = default;
	explicit ResourceManager(Runtime* runtime) : Object(runtime);
};