#include "../Inc/Runtime.h"

#include "../Inc/World.h"

#include "../../Audio/Inc/AudioManager.h"
#include "../../Config/Inc/ConfigManager.h"
#include "../../Input/Inc/InputManager.h"
#include "../../Networking/Inc/NetworkManager.h"
#include "../../Rendering/Inc/RenderManager.h"
#include "../../Resource/Inc/ResourceManager.h"
#include "../../Script/Inc/ScriptManager.h"
#include "../Inc/StatsManager.h"


bool Runtime::Initialize()
{
	CreateManagers();
	return ValidManagers();
}

void Runtime::Tick() const
{
	if (IsRunning() && HasWorld())
	{
		world_->Tick(GetStatsManager()->GetDeltaTime());
	}
}

void Runtime::Shutdown()
{
	world_ = nullptr;

	audioManager_	 = nullptr;
	configManager_	 = nullptr;
	inputManager_	 = nullptr;
	networkManager_  = nullptr;
	renderManager_	 = nullptr;
	resourceManager_ = nullptr;
	scriptManager_	 = nullptr;
	statsManager_	 = nullptr;

	for (Object* object : GetObjects())
	{
		DeleteObject(object);
	}

	objects_.Clear();

	Exit();
}

bool Runtime::IsRunning() const
{
	return running_;
}

void Runtime::SetResultString(const String& result)
{
	exitResult_ = result;
}

void Runtime::Exit()
{
	running_ = false;
}

bool Runtime::HasWorld() const
{
	return world_ != nullptr;
}

template<typename Type>
Type* Runtime::CreateObject()
{
	if (!IsChildOf<Type, Object>())
	{
		ERROR("Invalid class type provided! The class type must derive from Object! Aborting CreateObject");
		return nullptr;
	}

	Type* newObject = new Type(this);

	if (!newObject)
	{
		ERROR("New object could not be created!");
		return nullptr;
	}

	if (!LeaseUUID(newObject))
	{
		ERROR("Could not lease UUID for new object!");
		DeleteObject(newObject);
		return nullptr;
	}

	newObject->Initialize();

	return newObject;
}

void Runtime::DeleteObject(Object* object)
{
	object->Shutdown();
	UnregisterObject(object);
	delete object;
}

Array<Object*> Runtime::GetObjects() const
{
	return objects_.GetValues();
}

template<typename Base, typename Derived>
bool Runtime::IsChildOf() const noexcept
{
	Derived temp;
	return dynamic_cast<Base*>(&temp) != nullptr;
}

StatsManager *Runtime::GetStatsManager() const
{
	return statsManager_;
}

bool Runtime::IsValidUUID(const uint64 uuid)
{
	return uuid != 0;
}

uint64 Runtime::GenerateUUID() const
{
	uint64 newUUID = Rand::Rand64();

	while (DoesUUIDExist(newUUID) || !IsValidUUID(newUUID))
	{
		newUUID = Rand::Rand64();
	}

	return newUUID;
}

bool Runtime::DoesUUIDExist(const uint64 uuid) const
{
	return objects_.ContainsKey(uuid);
}

bool Runtime::LeaseUUID(Object* object)
{
	if (!object)
	{
		ERROR(String("Cannot lease UUID for invalid object!"));
		return false;
	}

	if (IsValidUUID(object->GetUUID()))
	{
		WARN("The provided object already has a valid UUID. If you want to reassign it, use RenewUUID() instead.");
		return false;
	}

	return RegisterObject(object, GenerateUUID());
}

bool Runtime::RenewUUID(Object* object)
{
	if (!object)
	{
		ERROR(String("Cannot renew UUID for invalid object!"));
		return false;
	}

	if (IsObjectRegistered(object))
	{
		if (!UnregisterObject(object))
		{
			ERROR(String("Could not unregister object ") + object->GetName().ToString() + "!");
			return false;
		}
	}

	return LeaseUUID(object);
}

bool Runtime::RequestUUID(Object* object, const uint64 uuid)
{
	if (!object)
	{
		ERROR(String("Cannot request UUID for invalid object!"));
		return false;
	}

	if (!IsValidUUID(uuid))
	{
		ERROR(String("Cannot request invalid UUID ") + uuid);
		return false;
	}

	if (DoesUUIDExist(uuid))
	{
		WARN(
			String("Could not assign UUID ") + uuid +
			" to object " + object->GetName().ToString() +
			" as that UUID is already assigned."
		);
		return false;
	}

	if (IsObjectRegistered(object))
	{
		if (!UnregisterObject(object))
		{
			ERROR(String("Could not unregister object ") + object->GetName().ToString());
			return false;
		}
	}

	return RegisterObject(object, uuid);
}

bool Runtime::DemandUUID(Object* object, const uint64 uuid)
{
	if (RequestUUID(object, uuid))
	{
		return true;
	}

	Object* existingLeaser = GetObjectFromUUID(uuid);

	if (!existingLeaser)
	{
		ERROR("UUID request failed, but the existing leaser could not be found.");
		return false;
	}

	if (!RenewUUID(existingLeaser))
	{
		ERROR(String("Could not renew UUID for existing leaser ") + existingLeaser->GetName().ToString());
		return false;
	}

	if (!UnregisterObject(object))
	{
		ERROR(String("Could not unregistered demanding object."));
		return false;
	}

	return RegisterObject(object, uuid);
}

bool Runtime::RegisterObject(Object* object, const uint64 uuid)
{
	if (!object)
	{
		ERROR("Cannot register invalid object!");
		return false;
	}

	if (IsObjectRegistered(object))
	{
		WARN(String("Cannot register object ") + object->GetName().ToString() + " as it is already registered.");
		return false;
	}

	if (!IsValidUUID(uuid))
	{
		ERROR(String("Cannot register object ") + object->GetName().ToString() + " with invalid UUID " + uuid);
		return false;
	}

	object->SetUUID(uuid);

	return objects_.Add(uuid, object);
}

bool Runtime::UnregisterObject(Object* object)
{
	if (!object)
	{
		ERROR("Cannot unregister invalid object!");
		return false;
	}

	if (IsObjectRegistered(object))
	{
		const uint64 uuid = object->GetUUID();
		object->SetUUID(0);
		return objects_.Remove(uuid);
	}

	WARN(String("Cannot unregister ") + object->GetName().ToString() + " as it is not registered to begin with.");
	return false;
}

Object* Runtime::GetObjectFromUUID(const uint64 uuid)
{
	return objects_.Get(uuid);
}

bool Runtime::IsObjectRegistered(const Object* object) const
{
	const uint64 uuid = object->GetUUID();

	if (!IsValidUUID(uuid))
	{
		return false;
	}

	return objects_.ContainsKey(uuid);
}

void Runtime::CreateManagers()
{
	configManager_	 = CreateObject<ConfigManager>();
	audioManager_	 = CreateObject<AudioManager>();
	inputManager_	 = CreateObject<InputManager>();
	networkManager_  = CreateObject<NetworkManager>();
	renderManager_	 = CreateObject<RenderManager>();
	resourceManager_ = CreateObject<ResourceManager>();
	scriptManager_	 = CreateObject<ScriptManager>();
	statsManager_	 = CreateObject<StatsManager>();
}

bool Runtime::ValidManagers() const
{
	return	configManager_	 != nullptr &&
			audioManager_	 != nullptr &&
			inputManager_	 != nullptr &&
			networkManager_  != nullptr &&
			renderManager_	 != nullptr &&
			resourceManager_ != nullptr &&
			scriptManager_	 != nullptr &&
			statsManager_	 != nullptr;
}