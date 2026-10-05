#pragma once

#include "../../Audio/Inc/AudioManager.h"
#include "../../Config/Inc/ConfigManager.h"
#include "../../Input/Inc/InputManager.h"
#include "../../Networking/Inc/NetworkManager.h"
#include "../../Rendering/Inc/RenderManager.h"
#include "../../Resource/Inc/ResourceManager.h"
#include "../../Script/Inc/ScriptManager.h"
#include "../Inc/UUIDManager.h"

#include "World.h"

#include <Core.h>

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
	Time&			 GetTime()			  noexcept;
	World&			 GetWorld()			  noexcept;

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