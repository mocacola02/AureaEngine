#pragma once

#include "Core.h"


class AudioManager final : public Object
{
public:
	explicit AudioManager(Runtime* runtime) : Object(runtime) {}
};