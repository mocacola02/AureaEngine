#pragma once

#include "CoreInc.h"


class EngineLoop : public Object
{
public:
	bool Initialize();
	void Tick();
	void Shutdown();

	bool IsRunning() const;

	String Exit();

private:
	bool running_ = false;
};