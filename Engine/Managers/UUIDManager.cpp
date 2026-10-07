#include "UUIDManager.h"

bool UUIDManager::Lease(Object* object)
{
	if (!object)
	{
		ERROR(String("Cannot renew UUID for invalid object pointer!"));
		return false;
	}

	if (IsObjectRegistered(object))
	{
		WARN(
			String("Cannot lease UUID for ") +
				GetObjectName(object) +
				" as it is already registered."+
				" If you want to reassign its UUID, use Renew()."
		);

		return false;
	}

	return RegisterObject(object, Generate());
}

bool UUIDManager::Renew(Object* object)
{
	if (!object)
	{
		ERROR(String("Cannot renew UUID for invalid object pointer!"));
		return false;
	}

	if (IsObjectRegistered(object))
	{
		if (!UnregisterObject(object))
		{
			ERROR(String("Failed to unregister object!"));
			return false;
		}
	}

	return Lease(object);
}

bool UUIDManager::Request(Object* object, const UUID& uuid)
{
	if (!object)
	{
		ERROR(String("Cannot request UUID for invalid object pointer!"));
		return false;
	}

	if (!uuid.IsValid())
	{
		ERROR(String("Cannot request invalid UUID ") + uuid.Value() + "!");
		return false;
	}

	if (IsUUIDRegistered(uuid))
	{
		const String registeredName = GetObjectName(GetObject(uuid));

		WARN(
			String("Could not assign UUID ") +
			uuid.Value() +
			" to object " +
			GetObjectName(object) +
			" as that UUID is already registered to " +
			registeredName
		);

		return false;
	}

	if (IsObjectRegistered(object))
	{
		if (!UnregisterObject(object))
		{
			ERROR(String("Failed to unregister object!"));
			return false;
		}
	}

	return RegisterObject(object, uuid);
}

bool UUIDManager::Demand(Object* object, const UUID& uuid)
{
	if (!object)
	{
		ERROR(String("Cannot demand UUID for invalid object pointer!"));
		return false;
	}

	if (!uuid.IsValid())
	{
		ERROR(String("Cannot request invalid UUID ") + uuid.Value() + "!");
		return false;
	}

	if (IsUUIDRegistered(uuid))
	{
		Object* currentLeaser = GetObject(uuid);

		if (!currentLeaser)
		{
			ERROR(String("UUID ") + uuid.Value() + " is registered, but the current leaser could not be identified!");
			return false;
		}

		Renew(currentLeaser);

		if (currentLeaser->GetUUID() == uuid)
		{
			ERROR(String("Failed to renew UUID for current leaser of ") + uuid.Value());
			return false;
		}
	}

	return Request(object, uuid);
}

bool UUIDManager::Release(const UUID& uuid)
{
	return UnregisterObject(GetObject(uuid));
}

Object* UUIDManager::GetObject(const UUID& uuid)
{
	if (!IsUUIDRegistered(uuid))
	{
		WARN(String("UUID ") + uuid.Value() + " is not registered to any object.");
		return nullptr;
	}

	return registry_.Get(uuid);
}

void UUIDManager::Clear()
{
	for (const UUID& uuid : GetUUIDs())
	{
		Release(uuid);
	}
}

Array<UUID> UUIDManager::GetUUIDs() const
{
	return registry_.GetKeys();
}

Array<Object*> UUIDManager::GetObjects() const
{
	return registry_.GetValues();
}

String UUIDManager::GetObjectName(const Object* object)
{
	return object->GetName().ToString();
}

UUID UUIDManager::Generate() const
{
	UUID newUUID = UUID(Rand::RandUInt64());

	constexpr uint8 maxAttempts = 100;
	uint8 attempts = 0;

	while (attempts < maxAttempts || IsUUIDRegistered(newUUID) || !newUUID.IsValid())
	{
		newUUID = Rand::RandUInt64();
		++attempts;
	}

	if (IsUUIDRegistered(newUUID) || !newUUID.IsValid())
	{
		ERROR(String("Failed to generate a UUID within ") + maxAttempts + " attempts!");
		return UUID(0);
	}

	return newUUID;
}

bool UUIDManager::IsUUIDRegistered(const UUID& uuid) const
{
	return registry_.ContainsKey(uuid);
}

bool UUIDManager::IsObjectRegistered(const Object* object) const
{
	return registry_.ContainsKey(object->GetUUID());
}

bool UUIDManager::RegisterObject(Object* object, const UUID& uuid)
{
	if (!object)
	{
		ERROR("Cannot register from invalid object pointer!");
		return false;
	}

	if (IsObjectRegistered(object))
	{
		WARN(String("Cannot register object ") + GetObjectName(object) + " as it is already registered.");
		return false;
	}

	if (!uuid.IsValid())
	{
		ERROR(String("Cannot register object ") + GetObjectName(object) + " with invalid UUID " + uuid.Value());
		return false;
	}

	object->SetUUID(uuid);
	return registry_.Add(uuid, object);
}

bool UUIDManager::UnregisterObject(Object* object)
{
	if (!object)
	{
		ERROR("Cannot unregister from invalid object pointer!");
		return false;
	}

	if (!IsObjectRegistered(object))
	{
		WARN(String("Cannot unregister ") + GetObjectName(object) + " as it is not registered to begin with.");
		return false;
	}

	if (!registry_.Remove(object->GetUUID()))
	{
		ERROR(String("Failed to unregister object ") + GetObjectName(object) + ".");
		return false;
	}

	object->SetUUID(0);
	return true;
}