#pragma once

#include <Core.h>

class Runtime;

//! The engine loop is the owner of all tickable objects and handles ticking them (go figure).
//! This is a virtual class that should be extended to have proper tick loop logic.
//! In AureaEngine, the default engine loop is the World, which owns WorldObjects and manages them
class EngineLoop : public Object
{
public:
	explicit EngineLoop(Runtime* runtime) : Object(runtime);

protected:
	//! Returns whether or not this EngineLoop is running.
	virtual bool IsRunning() const ;
	virtual void SetIsRunning(bool isRunning);

	//! Sets the exit code and sets to stop running.
	virtual void Exit(int32 code);
	//! Returns the current exit code.
	virtual int32 GetExitCode() const;

	//! Creates and initializes any relevant objects and sets running_ to true.
	//! Returns whether or not initialization was successful.
	virtual bool LoopInit();
	//! Ticks the EngineLoop and any tickable objects it owns.
	virtual void Tick(double deltaTime) = 0;
};