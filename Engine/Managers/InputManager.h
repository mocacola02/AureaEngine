#pragma once

#include <../../Core/Core.h>


class InputManager final : public Object
{
public:
	InputManager() = default;
	explicit InputManager(Runtime* runtime) : Object(runtime) {}
};