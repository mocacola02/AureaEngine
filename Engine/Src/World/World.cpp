#include "../../Inc/World/World.h"
#include "../../Inc/World/WorldObject.h"


template<typename T, typename... Args>
T* World::SpawnObject(Args&&... args)
{
	unique_ptr<T> object = make_unique<T>(Forward<Args>(args)...);

	T* objectPtr = object.get();

	objectPtr->Initialize();
}

bool World::DestroyObject(WorldObject *object)
{
	if (!object)
	{
		return false;
	}

	bool found = false;

	for (const unique_ptr<WorldObject>& existing : objects_)
	{
		if (existing.get() == object)
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		return false;
	}

	if (object->IsPendingDestroy())
	{
		return true;
	}

	object->Destroy();

	return true;
}

void World::DestroyPendingObjects()
{
}

Array<unique_ptr<WorldObject>>& World::GetObjects()
{

}

const Array<unique_ptr<WorldObject>>& World::GetObjects() const
{
	return {};
}

WorldObject* World::FindObjectByID(uint32 id)
{

}

const WorldObject* World::FindObjectByID(uint32 id) const
{

}

WorldObject* World::FindObjectByName(const Name &name)
{

}

const WorldObject* World::FindObjectByName(const Name &name) const
{

}

Array<WorldObject*> &World::GetRootObjects() const
{

}

uint32 World::GetObjectCount() const
{
	return objects_.Count();
}

bool World::Initialize()
{
	for (const unique_ptr<WorldObject>& object : objects_)
	{
		if (!object)
		{
			continue;
		}

		if (object->IsPendingDestroy())
		{
			continue;
		}

		object->Start();
	}

	SetIsRunning(true);
	return true;
}

void World::Tick(double deltaTime)
{
	if (!IsRunning())
	{
		return;
	}

	for (const unique_ptr<WorldObject>&  object : objects_)
	{
		if (!object)
		{
			continue;
		}

		if (object->IsPendingDestroy())
		{
			continue;
		}

		object->Tick(deltaTime);
	}

	DestroyPendingObjects();
}

void World::Shutdown()
{
	for (const unique_ptr<WorldObject>& object : objects_)
	{
		if (!object)
		{
			continue;
		}

		object->RemoveParent();
	}

	for (const unique_ptr<WorldObject>& object : objects_)
	{
		if (!object)
		{
			continue;
		}

		if (!object->IsPendingDestroy())
		{
			object->Destroy();
		}
	}

	DestroyPendingObjects();

	objects_.Clear();

	SetIsRunning(false);
}