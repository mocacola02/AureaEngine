#include "../Inc/EngineLoop.h"

#include "SDL3/SDL_messagebox.h"


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

bool EngineLoop::Initialize()
{
	running_ = true;
	return true;
}

void EngineLoop::InternalFatal(
		const String& message,
		const int32 exitCode,
		const char* file,
		const char* function,
		const uint32 line
)
{
	Log::InternalFatal(message, file, function, line);

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "FATAL ERROR", message.CStr(), nullptr);

	Exit(exitCode);
}