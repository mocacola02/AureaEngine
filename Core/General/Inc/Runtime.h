#pragma once

#include "Object.h"

//! The Runtime tracks core objects and data relevant during the program's runtime.
//! This is a virtual class that should be extended to have proper runtime logic.
//! In Aurea Engine, the primary runtime is the EngineRuntime, which manages the
//! EngineLoop/World and various managers. See EngineRuntime for more info.
class Runtime : public Object
{
public:
	virtual bool Initialize() = 0;
	virtual void Tick(double deltaTime_) = 0;
	virtual void Shutdown() = 0;

	virtual void SetIsRunning(bool isRunning) = 0;
	[[nodiscard]] virtual bool IsRunning() const = 0;

	[[nodiscard]] virtual int32 GetExitCode() const = 0;

private:
	bool running_ = false;
};