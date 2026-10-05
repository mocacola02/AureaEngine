#include "../Inc/Time.h"

#include <SDL3/SDL_timer.h>


void Time::Start()
{
	startMs_ = SDL_GetTicks();
	prevMs_  = startMs_;

	elapsedMs_	 = 0;
	deltaTime_	 = 0.0;
}

double Time::Tick()
{
	const uint64 currentMs = SDL_GetTicks();
	const double delta = static_cast<double>(currentMs - prevMs_) / 1000;

	prevMs_ = currentMs;

	elapsedMs_ = currentMs - startMs_;

	deltaTime_ = delta;

	return deltaTime_;
}

uint64 Time::GetElapsedMilliseconds() const
{
	return elapsedMs_;
}

double Time::GetDeltaTime() const
{
	return deltaTime_;
}