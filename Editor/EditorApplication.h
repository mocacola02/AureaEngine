#pragma once

#include "Inc/Application.h"
#include "Inc/EngineRuntime.h"


class EditorApplication final : public Application
{
public:
	//! Creates and initializes the runtime.
	bool Initialize() override
	{
		runtime_ = new EngineRuntime;
		return runtime_->Initialize();
	}

	//! Application loop that ticks the runtime.
	void Run() const override
	{
		while (runtime_ && runtime_->IsRunning())
		{
			// TODO: Placeholder deltaTime, replace with actual time
			runtime_->Tick(0.333);
		}
	}

	//! Shuts down and destroys the runtime.
	void Shutdown() override
	{
		runtime_->Shutdown();
		delete runtime_;
		runtime_ = nullptr;
	}

	//! Returns the runtime's exit code.
	//! If no runtime is found, returns -1.
	[[nodiscard]] int32 GetExitCode() const override
	{
		if (runtime_)
		{
			return runtime_->GetExitCode();
		}

		return -1;
	}

private:
	//! Pointer to the current runtime.
	Runtime* runtime_ = nullptr;
};