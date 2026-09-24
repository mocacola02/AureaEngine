#pragma once

#include "CoreInc.h"

class EngineRuntime;

//! The engine loop is the owner of all tickable objects and handles ticking them (go figure).
//! This is a virtual class that should be extended to have proper tick loop logic.
//! In AureaEngine, the default engine loop is the World, which owns WorldObjects and manages them
class EngineLoop : public Object
{
public:
	void Initialize() override;

protected:
	// Runtime should have access, anything else should communicate via Runtime
	// CONSIDER: Maybe this should be reverse? If the EngineLoop/World owns the "higher level" objects maybe EngineLoop/World should be more open?
	friend class Runtime;

	//! Tracks if this EngineLoop is running or not.
	bool running_ = false;
	//! Code to return to the Application when exiting. Set via Exit()
	int32 exitCode_ = 0;

	//! Returns whether or not this EngineLoop is running.
	[[nodiscard]] virtual bool IsRunning() const ;
	virtual void SetIsRunning(bool isRunning);

	//! Sets the exit code and sets to stop running.
	virtual void Exit(int32 code);
	//! Returns the current exit code.
	[[nodiscard]] virtual int32 GetExitCode() const;

	//! Creates and initializes any relevant objects and sets running_ to true.
	//! Returns whether or not initialization was successful.
	virtual bool LoopInit();
	//! Ticks the EngineLoop and any tickable objects it owns.
	virtual void Tick(double deltaTime) = 0;

	[[nodiscard]] EngineRuntime* GetRuntime() const;

private:
	EngineRuntime* runtime_ = nullptr;
};