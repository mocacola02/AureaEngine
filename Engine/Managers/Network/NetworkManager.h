#pragma once

#include "Core.h"


class NetworkManager final : public Object
{
public:
	explicit NetworkManager(Runtime* runtime) : Object(runtime) {}
};