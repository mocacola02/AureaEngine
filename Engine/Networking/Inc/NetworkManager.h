#pragma once

#include <Core.h>


class NetworkManager final : public Object
{
public:
	NetworkManager() = default;
	explicit NetworkManager(Runtime* runtime) : Object(runtime);
};