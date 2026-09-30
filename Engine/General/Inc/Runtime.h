#pragma once

#include <Core.h>

class World;
class AudioManager;
class ConfigManager;
class InputManager;
class NetworkManager;
class RenderManager;
class ResourceManager;
class ScriptManager;
class StatsManager;

//! The engine runtime handles the engine's various managers,
//! and it owns and ticks the EngineLoop (World, by default).
class Runtime
{
public:
	Runtime() = default;
	~Runtime() = default;

	bool Initialize();
	void Tick() const;
	void Shutdown();

	bool IsRunning() const;

	void SetResultString(const String& result);
	void Exit();

	bool HasWorld() const;

	template <typename Type>
	Type* CreateObject();

	void DeleteObject(Object* object);

	Array<Object*> GetObjects() const;

	template<typename Base, typename Derived>
	bool IsChildOf() const noexcept;

	// Manager Helpers
	StatsManager* GetStatsManager() const;


	// UUID

	//! Returns whether or not a given UUID is valid.
	//! Currently, any UUID that is not equal to 0 is valid.
	static bool IsValidUUID(uint64 uuid);

	//! Generates a random uint64 value that is not registered in the objects dictionary.
	uint64 GenerateUUID() const;

	//! Returns whether or not a given UUID is registered in the objects dictionary.
	bool DoesUUIDExist(uint64 uuid) const;

	//! Generates and registers an object with a new UUID, only if the object does not have a valid UUID.
	bool LeaseUUID(Object* object);

	//! Generates a new UUID for a given object, even if the object already has a UUID.
	bool RenewUUID(Object* object);

	//! Requests a given UUID to be registered to a given object and returns whether or not it was successful.
	//! If the UUID is already taken, the request will fail. To force a request, use DemandUUID().
	bool RequestUUID(Object* object, uint64 uuid);

	//! Demands a given UUID to be registered to a given object and returns whether or not it was successful.
	//! If the UUID is already taken, the object that currently owns it will have its UUID renewed,
	//! freeing the demanded UUID for use.
	//! This function should only return false as the result of an error.
	bool DemandUUID(Object* object, uint64 uuid);

	//! Registers an object in the runtime with a given UUID and returns if it was successful.
	bool RegisterObject(Object* object, uint64 uuid);

	//! Unregisters a given object in the runtime, freeing its UUID and returning if successful.
	bool UnregisterObject(Object* object);

	//! Returns a pointer for an object with a given UUID.
	Object* GetObjectFromUUID(uint64 uuid);

	//! Returns whether or not a given object is registered in the runtime.
	bool IsObjectRegistered(const Object* object) const;

private:
	bool running_ = false;

	String exitResult_ = "Exited with no errors.";

	World* world_ = nullptr;

	Dictionary<uint32, Object*> objects_;

	// Managers
	AudioManager*	 audioManager_	  = nullptr;
	ConfigManager*	 configManager_	  = nullptr;
	InputManager*	 inputManager_	  = nullptr;
	NetworkManager*	 networkManager_  = nullptr;
	RenderManager*	 renderManager_	  = nullptr;
	ResourceManager* resourceManager_ = nullptr;
	ScriptManager*	 scriptManager_	  = nullptr;
	StatsManager*	 statsManager_	  = nullptr;

	void CreateManagers();
	bool ValidManagers() const;
};