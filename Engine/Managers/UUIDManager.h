#pragma once

#include "Core.h"


class UUIDManager : public Object
{
public:
	UUIDManager() = default;
	explicit UUIDManager(Runtime* runtime) : Object(runtime) {}

	bool Lease(Object* object);
	bool Renew(Object* object);

	bool Request(Object* object, const UUID& uuid);
	bool Demand (Object* object, const UUID& uuid);

	bool Release(const UUID& uuid);

	Object* GetObject(const UUID& uuid);

protected:
	friend class Runtime;

	void Clear();

	Array<UUID> GetUUIDs() const;
	Array<Object*> GetObjects() const;

private:
	Dictionary<UUID, Object*> registry_;

	static String GetObjectName(const Object *object);

	UUID Generate() const;

	bool IsUUIDRegistered(const UUID& uuid) const;
	bool IsObjectRegistered(const Object* object) const;

	bool RegisterObject(Object* object, const UUID& uuid);
	bool UnregisterObject(Object* object);
};