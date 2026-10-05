#pragma once

#include <Core.h>

class Runtime;

//! The engine loop is the owner of all tickable objects and handles ticking them (go figure).
//! This is a virtual class that should be extended to have proper tick loop logic.
//! In AureaEngine, the default engine loop is the World, which owns WorldObjects and manages them
class EngineLoop : public Object
{
public:
	explicit EngineLoop(Runtime* runtime) : Object(runtime) {}

protected:
	//! Returns whether or not this EngineLoop is running.
	virtual bool IsRunning() const ;
	virtual void SetIsRunning(bool isRunning);

	//! Ticks the EngineLoop and any tickable objects it owns.
	virtual void Tick(double deltaTime) = 0;
};