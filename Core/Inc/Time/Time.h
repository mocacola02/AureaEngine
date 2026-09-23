#pragma once

#include "../Object.h"
#include "PlatformTime.h"


class Time : public Object
{
public:
	void Start()
	{
		PlatformTime::Initialize();

		startTime_    = PlatformTime::GetSeconds();

		previousTime_ = startTime_;

		elapsedTime_ = 0.0;
		deltaTime_	 = 0.0;
		fps_		 = 0.0;
	}

	void Tick()
	{
		const double currentTime = PlatformTime::GetSeconds();
		const double delta = currentTime - previousTime_;

		previousTime_ = currentTime;

		elapsedTime_ = currentTime - startTime_;

		deltaTime_ = delta;

		if (deltaTime_ > 0.0)
		{
			fps_ = 1.0 / deltaTime_;
		}
		else
		{
			fps_ = 0.0;
		}
	}

	[[nodiscard]] double GetDeltaTime() const
	{
		return deltaTime_;
	}

	[[nodiscard]] double GetElapsedTime() const
	{
		return elapsedTime_;
	}

	[[nodiscard]] double GetFPS() const
	{
		return fps_;
	}

private:
	double startTime_	 = 0.0;
	double previousTime_ = 0.0;
	double elapsedTime_  = 0.0;

	double deltaTime_ = 0.0;
	double fps_		  = 0.0;
};