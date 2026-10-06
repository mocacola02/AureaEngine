#pragma once

//! The Application is where the program's entrypoint connects to the engine.
//! The Application's primary job is to initiate the proper startup behavior and manage the runtime.
//! This is a virtual class that should, in theory, have a child class for each executable.
//! For example, Aurea Engine comes with two primary executables: AureaEd and Game (or whatever the project name is).
//! As such, there are two Application child classes "Editor" and "Game" in their respective libraries.
class Application
{
public:
	//! Constructor
	Application() = default;

	//! Destructor
	virtual ~Application() = default;

	//! Called on application launch
	virtual bool Initialize() = 0;

	//! Application loop that ticks the runtime.
	virtual void Run() const = 0;

	//! Is the application running
	virtual bool IsRunning() const = 0;

	//! Called before closing application
	virtual void Shutdown() = 0; 
};