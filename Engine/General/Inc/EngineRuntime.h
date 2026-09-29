#pragma once

#include "World.h"

#include "../../Audio/Inc/AudioManager.h"
#include "../../Config/Inc/ConfigManager.h"
#include "../../Input/Inc/InputManager.h"
#include "../../Networking/Inc/NetworkManager.h"
#include "../../Rendering/Inc/RenderManager.h"
#include "../../Resource/Inc/ResourceManager.h"
#include "../../Script/Inc/ScriptManager.h"
#include "StatsManager.h"
#include "../../Object/Inc/UUIDManager.h"

#include <Core.h>

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

	//! Sets the exit code and sets to stop running.
	void Exit(int32 code);
	[[nodiscard]] int32 GetExitCode() const override;

private:
	World world_;

	// Managers
	AudioManager	 audioManager_;
	ConfigManager	 configManager_;
	InputManager	 inputManager_;
	NetworkManager	 networkManager_;
	RenderManager	 renderManager_;
	ResourceManager	 resourceManager_;
	ScriptManager	 scriptManager_;
	StatsManager	 statsManager_;
	UUIDManager		 uuidManager_;
};