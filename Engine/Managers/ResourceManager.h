#pragma once

#include "Core.h"


class ResourceManager final : public Object
{
public:
	explicit ResourceManager(Runtime* runtime) : Object(runtime) {}
};