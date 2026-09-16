#include "../../Inc/Time/PlatformTime.h"

#if defined(__linux__)

#include <Windows.h>

namespace
{
	bool initialized = false;
}

void PlatformTime::Initialize()
{
	initialized = true;
}

double PlatformTime::GetSeconds()
{
	if (!initialized)
	{
		Initialize();
	}

	timespec time{};

	clock_gettime(CLOCK_MONOTONIC, &time);

	return static_cast<double>(time.tv_sec) + static_cast<double>(time.tv_nsec) / 1000000000.0;
}

double PlatformTime::GetMilliseconds()
{
	return GetSeconds() * 1000.0;
}

double PlatformTime::GetMicroseconds()
{
	return GetSeconds() * 1000000.0;
}

#endif