#pragma once

#include "Core.h"


class ScriptManager final : public Object
{
public:
	explicit ScriptManager(Runtime* runtime) : Object(runtime) {}
};