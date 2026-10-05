#pragma once

#include <Core.h>


class ScriptManager final : public Object
{
public:
	ScriptManager() = default;
	explicit ScriptManager(Runtime* runtime) : Object(runtime);
};