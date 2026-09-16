#include "../../Inc/Time/PlatformTime.h"

#if defined(_WIN32)

#include <Windows.h>

namespace
{
	bool initialized = false;
	double secondsPerCount = 0.0;
}

void PlatformTime::Initialize()
{
	if (initialized)
	{
		return;
	}

	LARGE_INTEGER frequency{};

	if (!QueryPerformanceFrequency(&frequency))
	{
		secondsPerCount = 0.0;
		return;
	}

	secondsPerCount = 1.0 / static_cast<double>(frequency.QuadPart);

	initialized = true;
}

double PlatformTime::GetSeconds()
{
	if (!initialized)
	{
		Initialize();
	}

	LARGE_INTEGER counter{};

	QueryPerformanceFrequency(&counter);

	return static_cast<double>(counter.QuadPart) * secondsPerCount;
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