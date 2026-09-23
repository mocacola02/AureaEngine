#pragma once

#include "CoreInc.h"

#include "EngineLoop.h"

#include "ConfigManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "WindowManager.h"

class EditorApplication;

//! The engine runtime handles the engine's various managers,
//! and it owns and ticks the EngineLoop (World, by default).
class EngineRuntime final : public Runtime
{
public:
	bool Initialize() override;
	void Tick(double deltaTime_) override;
	void Shutdown() override;

	void SetIsRunning(bool isRunning) override;
	[[nodiscard]] bool IsRunning() const override;

	[[nodiscard]] int32 GetExitCode() const override;

private:
	EngineLoop*	   engineLoop_	  = nullptr;
	ConfigManager* configManager_ = nullptr;
	RenderManager* renderManager_ = nullptr;
	WindowManager* windowManager_ = nullptr;
	InputManager*  inputManager_  = nullptr;
};