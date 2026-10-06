#pragma once

#include "../Object.h"

// TODO: Add averaged FPS measurement

class Time : public Object
{
public:
	Time() = default;
	explicit Time(Runtime* runtime) : Object(runtime) {}

	void Start();

	double Tick();

	uint64 GetElapsedMilliseconds() const;
	double GetDeltaTime() const;

private:
	uint64 startMs_		= 0.0;
	uint64 prevMs_		= 0.0;
	uint64 elapsedMs_	= 0.0;

	double deltaTime_ = 0.0;
};