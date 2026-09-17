#pragma once

#include "EngineLoop.h"


class Application : public Object
{
public:
	bool Initialize()
	{
		loop_ = new EngineLoop();
		return loop_->Initialize();
	}


	void Run() const
	{
		while (loop_->IsRunning())
		{
			loop_->Tick();
		}
	}

	void Shutdown()
	{
		loop_->Shutdown();

		delete loop_;
		loop_ = nullptr;
	}

	void SetExitCode(const int32 result)
	{
		exitCode_ = result;
	}

	int32 GetExitCode() const
	{
		return exitCode_;
	}

private:
	int32 exitCode_ = 0;
	EngineLoop* loop_ = nullptr;
};