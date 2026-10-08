#include "World.h"

WorldObject* World::GetRootObject()
{
	return &rootObject_;
}

const WorldObject* World::GetRootObject() const
{
	return &rootObject_;
}

Array<WorldObject*> World::GetWorldObjects()
{
	Array<WorldObject*> objects;

	objects.Add(&rootObject_);

	for (WorldObject* object : rootObject_.GetDescendents())
	{
		objects.Add(object);
	}

	return objects;
}

template<typename Type>
Array<Type*> World::GetWorldObjectsOfType()
{
	Array<Type*> objects;

	if (!IsClassBasedOn<Type, WorldObject>())
	{
		WARN("Provided type must be based on WorldObject. Returning empty array.");
		return objects;
	}

	for (WorldObject* object : rootObject_.GetDescendents())
	{
		if (object->IsOfType<Type>())
		{
			objects.Add(object);
		}
	}

	return objects;
}

template<typename Base, typename Derived>
bool World::IsClassBasedOn() const
{
	return runtime_->IsClassBasedOn<Base, Derived>();
}

void World::DestroyPendingObjects()
{
	for (WorldObject* object : GetWorldObjects())
	{
		if (object->IsPendingDestroy())
		{
			object->OnDestroy();
			runtime_->GetUUIDManager().Release(object->GetUUID());
			delete object;
		}
	}
}

bool World::IsPaused() const
{
	return paused_;
}

bool World::Initialize()
{
	if (!runtime_)
	{
		ERROR("World does not have a pointer to the runtime!");
		return false;
	}

	rootObject_.SetTickMode(TickMode::Always);

	return true;
}

void World::Tick(const double deltaTime)
{
	if (rootObject_.ShouldTick(deltaTime))
	{
		for (WorldObject* object : GetTickList(deltaTime))
		{
			object->Tick(deltaTime);
		}
	}
}

void World::Shutdown()
{
	for (WorldObject* object : GetWorldObjects())
	{
		object->Destroy();
	}

	DestroyPendingObjects();

	runtime_ = nullptr;
}

Array<WorldObject*> World::GetTickList(const double deltaTime)
{
	Array<WorldObject*> tickList;

	for (WorldObject* object : GetWorldObjects())
	{
		if (object->ShouldTick(deltaTime))
		{
			tickList.Add(object);
		}
	}

	return tickList;
}
