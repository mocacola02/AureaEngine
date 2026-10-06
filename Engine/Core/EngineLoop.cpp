#include "../../Core/EngineLoop.h"
#include "Runtime.h"

bool EngineLoop::Initialize()
{
	if (!LoopInit())
	{
		ERROR("Could not initialize EngineLoop.");
		return false;
	}

	return true;
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

Runtime* EngineLoop::GetRuntime() const
{
	return runtime_;
}