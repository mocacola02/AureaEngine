#pragma once

#include <../../Core/Core.h>

class AudioManager final : public Object
{
public:
	AudioManager() : Object() {}
	explicit AudioManager(Runtime* runtime) : Object(runtime) {}
};