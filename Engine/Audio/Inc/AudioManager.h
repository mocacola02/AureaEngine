#pragma once

#include <Core.h>

class AudioManager final : public Object
{
public:
    AudioManager() = default;
    explicit AudioManager(Runtime* runtime) : Object(runtime);
};