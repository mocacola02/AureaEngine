#pragma once

#include "../../Audio/Inc/AudioManager.h"
#include "../../Config/Inc/ConfigManager.h"
#include "Managers/InputManager.h"
#include "Managers/NetworkManager.h"
#include "../Managers/Rendering/RenderManager.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/ScriptManager.h"
#include "../Managers/UUIDManager.h"

#include "../../Object/World.h"

#include <../../Core/Core.h>

//! The engine runtime handles the engine's various managers,
//! and it owns and ticks the EngineLoop (World, by default).
class Runtime
{
public:
	Runtime() :  uuidManager_(this), audioManager_(this), configManager_(this),
				 inputManager_(this), networkManager_(this), renderManager_(this),
				 resourceManager_(this), scriptManager_(this), time_(this), world_(this) {}

	~Runtime() = default;

	bool Initialize();
	void Run();
	void Shutdown();

	bool IsRunning() const;

	void SetResultString(const String& result);
	void Exit();

	template <typename Type>
	Type* CreateObject();

	void DeleteObject(Object* object);

	Array<Object*> GetObjects();

	template<typename Type>
	Array<Type*> GetObjectsOfType();

	template<typename Base, typename Derived>
	bool IsBasedOn() const noexcept;

	// Manager Helpers
	AudioManager&	 GetAudioManager()	  noexcept;
	ConfigManager&	 GetConfigManager()	  noexcept;
	InputManager&	 GetInputManager()	  noexcept;
	NetworkManager&  GetNetworkManager()  noexcept;
	RenderManager&	 GetRenderManager()   noexcept;
	ResourceManager& GetResourceManager() noexcept;
	ScriptManager&	 GetScriptManager()	  noexcept;
	UUIDManager&	 GetUUIDManager()	  noexcept;

	Time&  GetTime()  noexcept;
	World& GetWorld() noexcept;

	const AudioManager&	   GetAudioManager()	const noexcept;
	const ConfigManager&   GetConfigManager()	const noexcept;
	const InputManager&	   GetInputManager()	const noexcept;
	const NetworkManager&  GetNetworkManager()	const noexcept;
	const RenderManager&   GetRenderManager()	const noexcept;
	const ResourceManager& GetResourceManager() const noexcept;
	const ScriptManager&   GetScriptManager()	const noexcept;
	const UUIDManager&	   GetUUIDManager()		const noexcept;

	const Time&	 GetTime()	const noexcept;
	const World& GetWorld() const noexcept;

private:
	bool running_ = false;

	String exitResult_ = "Exited with no errors.";

	UUIDManager		 uuidManager_;
	AudioManager	 audioManager_;
	ConfigManager	 configManager_;
	InputManager	 inputManager_;
	NetworkManager	 networkManager_;
	RenderManager	 renderManager_;
	ResourceManager	 resourceManager_;
	ScriptManager	 scriptManager_;

	Time time_;
	World world_;
};