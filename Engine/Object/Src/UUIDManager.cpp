#include "../Inc/UUIDManager.h"

#include <SDL3/SDL_stdinc.h>


uint64 UUIDManager::Lease(Object* leaser)
{
	if (!leaser)
	{
		return 0;
	}

	uint64 newUUID = 0;
	while (DoesUUIDExist(newUUID))
	{
		newUUID = Generate();
	}

	Register(newUUID, leaser);
	return newUUID;
}

uint64 UUIDManager::Renew(Object* leaser)
{
	if (!leaser)
	{
		return 0;
	}

	if (const uint64 leaserUUID = leaser->GetUUID(); DoesUUIDExist(leaser->GetUUID()))
	{
		Release(leaserUUID);
	}

	return Lease(leaser);
}

bool UUIDManager::Request(const uint64 uuid, Object* leaser)
{
	if (!DoesUUIDExist(uuid))
	{
		Register(uuid, leaser);
		return true;
	}

	return false;
}

bool UUIDManager::Demand(const uint64 uuid, Object* leaser)
{
	if (!Request(uuid, leaser))
	{
		Object* existingLeaser = GetObjectFromUUID(uuid);
		existingLeaser->RenewUUID();
	}

	return Request(uuid, leaser);
}

void UUIDManager::Release(const uint64 uuid)
{
	if (DoesUUIDExist(uuid))
	{
		uuidDictionary_.Remove(uuid);
	}
}

bool UUIDManager::DoesUUIDExist(const uint64 uuid) const
{
	return uuidDictionary_.Contains(uuid);
}

Object* UUIDManager::GetObjectFromUUID(const uint64 uuid) const
{
	if (DoesUUIDExist(uuid))
	{
		return uuidDictionary_.Get(uuid);
	}

	WARN(String("UUID ") + String(uuid) + String(" is not registered."));
	return nullptr;
}

uint64 UUIDManager::Generate()
{
	const uint32 high = SDL_rand_bits();
	const uint32 low  = SDL_rand_bits();

	return (static_cast<uint64>(high) << 32) | low;
}

void UUIDManager::Register(const uint64 uuid, Object* leaser)
{
	if (DoesUUIDExist(uuid))
	{
		const Object* existingLeaser = GetObjectFromUUID(uuid);
		ERROR(String("UUID ") + String(uuid) + String(" is already registered to ") + existingLeaser->GetName().ToString());
		return;
	}

	uuidDictionary_.Add(uuid, leaser);
}