#pragma once

#include "../../../Core/General/Inc/Object.h"


class UUIDManager : public Object
{
public:
	UUIDManager() = default;
	explicit UUIDManager(Runtime* runtime) : Object(runtime) {}

	bool Lease(Object* object)
	{
		if (!object)
		{
			ERROR(String("Cannot renew UUID for invalid object pointer!"));
			return false;
		}

		if (IsObjectRegistered(object))
		{
			WARN(String("Cannot lease UUID for ") + GetObjectName(object) + " as it is already registered. If you want to reassign it, use Renew().");
			return false;
		}

		return RegisterObject(object, Generate());
	}

	bool Renew(Object* object)
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

	bool Request(Object* object, const uint32 uuid)
	{
		if (!object)
		{
			ERROR(String("Cannot request UUID for invalid object pointer!"));
			return false;
		}

		if (!IsUUIDValid(uuid))
		{
			ERROR(String("Cannot request invalid UUID ") + uuid);
			return false;
		}

		if (IsUUIDRegistered(uuid))
		{
			const String registeredName = GetObjectName(GetObject(uuid));
			WARN(String("Could not assign UUID ") + uuid +
				" to object " + GetObjectName(object) +
				" as that UUID is already registered to " + registeredName
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

	bool Demand(Object* object, const uint32 uuid)
	{
		if (!object)
		{
			ERROR(String("Cannot request UUID for invalid object pointer!"));
			return false;
		}

		if (!IsUUIDValid(uuid))
		{
			ERROR(String("Cannot request invalid UUID ") + uuid);
			return false;
		}

		if (IsUUIDRegistered(uuid))
		{
			Object* existingLeaser = GetObject(uuid);

			if (!existingLeaser)
			{
				ERROR("Could not identify the existing leaser!");
				return false;
			}

			Renew(existingLeaser);

			if (existingLeaser->GetUUID() == uuid)
			{
				ERROR("Failed to renew UUID for the existing leaser!");
				return false;
			}
		}

		return Request(object, uuid);
	}

	bool Release(const uint32 uuid)
	{
		return UnregisterObject(GetObject(uuid));
	}

	Object* GetObject(const uint32 uuid)
	{
		if (!IsUUIDRegistered(uuid))
		{
			WARN(String("UUID " ) + uuid + " is not registered to any object.");
			return nullptr;
		}

		return registry_.Get(uuid);
	}

protected:
	friend class Runtime;

	void Clear()
	{
		for (const uint32 uuid : registry_.GetKeys())
		{
			Release(uuid);
		}
	}

	Array<Object*> GetObjects() const
	{
		return registry_.GetValues();
	}

private:
	Dictionary<uint32, Object*> registry_;

	static bool IsUUIDValid(const uint32 uuid)
	{
		return uuid > 0;
	}

	static String GetObjectName(const Object *object)
	{
		return object->GetName().ToString();
	}

	bool IsUUIDRegistered(const uint32 uuid) const
	{
		return registry_.ContainsKey(uuid);
	}

	bool IsObjectRegistered(const Object* object) const
	{
		return registry_.ContainsKey(object->GetUUID());
	}

	uint32 Generate() const
	{
		constexpr uint16 maxAttempts = 1000;
		uint16 attempts = 0;

		uint32 newUUID = Rand::Rand32();

		while (attempts > maxAttempts || registry_.ContainsKey(newUUID) || !IsUUIDValid(newUUID))
		{
			newUUID = Rand::Rand32();
			++attempts;
		}

		if (attempts > maxAttempts)
		{
			ERROR(String("Failed to generate a UUID within ") + String(maxAttempts) + " attempts!");
		}

		return newUUID;
	}

	bool RegisterObject(Object* object, const uint32 uuid)
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

		if (!IsUUIDValid(uuid))
		{
			ERROR(String("Cannot register object ") + GetObjectName(object) + " with invalid UUID " + uuid);
			return false;
		}

		object->SetUUID(uuid);

		return registry_.Add(uuid, object);
	}

	bool UnregisterObject(Object* object)
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

		const uint32 uuid = object->GetUUID();
		object->SetUUID(0);
		return registry_.Remove(uuid);
	}
};