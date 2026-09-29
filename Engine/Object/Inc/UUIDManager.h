#pragma once

#include <Core.h>

// TODO: Figure out UUID assignment order of operations

class UUIDManager final : public Object
{
public:
	uint64 Lease(Object* leaser);
	uint64 Renew(Object* leaser);

	bool Request(uint64 uuid, Object* leaser);
	bool Demand(uint64 uuid,  Object* leaser);

	void Release(uint64 uuid);

	[[nodiscard]] bool DoesUUIDExist(uint64 uuid) const;

	[[nodiscard]] Object* GetObjectFromUUID(uint64 uuid) const;

private:
	Dictionary<uint64, Object*> uuidDictionary_;

	static uint64 Generate();

	void Register(uint64 uuid, Object* leaser);
};