#pragma once

#include "Object.h"
#include "Runtime.h"

//! The Application is where the program's entrypoint connects to the engine.
//! The Application's primary job is to create and track the runtime, which is typically the Engine class.
//! This is a virtual class that should, in theory, have a child class for each executable.
//! For example, Aurea Engine comes with two primary executables: AureaEd and Game (or whatever the project name is).
//! As such, there are two Application child classes "Editor" and "Game" in their respective libraries.
class Application : public Object
{
public:
	//! Creates and initializes the runtime.
	virtual bool Initialize() = 0;

	//! Application loop that ticks the runtime.
	virtual void Run() const = 0;

	//! Shuts down and destroys the runtime.
	virtual void Shutdown() = 0;

	//! Returns the runtime's exit code.
	//! If no runtime is found, returns -1.
	[[nodiscard]] virtual int32 GetExitCode() const;

private:
	//! Pointer to the current runtime.
	Runtime* runtime_ = nullptr;
};