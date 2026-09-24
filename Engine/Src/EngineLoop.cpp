#include "../Inc/EngineLoop.h"
#include "../Inc/EngineRuntime.h"

void EngineLoop::Initialize()
{
	if (!LoopInit())
	{
		GetRuntime()->FATAL("Could not initialize EngineLoop.", -1);
	}
}

bool EngineLoop::IsRunning() const
{
	return running_;
}

void EngineLoop::SetIsRunning(const bool isRunning)
{
	running_ = isRunning;
}

void EngineLoop::Exit(const int32 code)
{
	exitCode_ = code;
	running_ = false;
}

int32 EngineLoop::GetExitCode() const
{
	return exitCode_;
}

bool EngineLoop::LoopInit()
{
	running_ = true;
	return true;
}

EngineRuntime* EngineLoop::GetRuntime() const
{
	return runtime_;
}