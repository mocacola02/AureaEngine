#include "../../Inc/World/World.h"
#include "../../Inc/World/WorldObject.h"

// TODO: Implement this for real
template<typename T, typename... Args>
T* World::SpawnObject(Args&&... args)
{
	unique_ptr<T> object = make_unique<T>(Forward<Args>(args)...);

	T* objectPtr = object.get();

	objectPtr->Initialize();

	return nullptr;
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
	for (uint32 i = objects_.Count(); i > 0; --i)
	{
		const uint32 index = i - 1;

		WorldObject* object = objects_[index].get();

		if (!object)
		{
			objects_.RemoveAt(index);
			continue;
		}

		if (!object->IsPendingDestroy())
		{
			continue;
		}

		object->RemoveParent(false);

		while (!object->GetChildren().IsEmpty())
		{
			WorldObject* child = object->GetChildren().Last();

			if (!child)
			{
				break;
			}

			child->RemoveParent(true);
		}

		objects_.RemoveAt(index);
	}
}

Array<unique_ptr<WorldObject>>& World::GetObjects()
{
	return objects_;
}

const Array<unique_ptr<WorldObject>>& World::GetObjects() const
{
	return objects_;
}

WorldObject* World::FindObjectByID(const uint32 id)
{
	for (uint32 i = 0; i < objects_.Count(); ++i)
	{
		WorldObject* object = objects_[i].get();

		if (!object)
		{
			objects_.RemoveAt(i);
			continue;
		}

		if (object->GetID() == id)
		{
			return object;
		}
	}

	return nullptr;
}

const WorldObject* World::FindObjectByID(const uint32 id) const
{
	for (uint32 i = 0; i < objects_.Count(); ++i)
	{
		const WorldObject* object = objects_[i].get();

		if (!object)
		{
			continue;
		}

		if (object->GetID() == id)
		{
			return object;
		}
	}

	return nullptr;
}

WorldObject* World::FindObjectByName(const Name& name)
{
	for (uint32 i = 0; i < objects_.Count(); ++i)
	{
		WorldObject* object = objects_[i].get();

		if (!object)
		{
			objects_.RemoveAt(i);
			continue;
		}

		if (object->GetName() == name)
		{
			return object;
		}
	}

	return nullptr;
}

const WorldObject* World::FindObjectByName(const Name &name) const
{
	for (uint32 i = 0; i < objects_.Count(); ++i)
	{
		const WorldObject* object = objects_[i].get();

		if (!object)
		{
			continue;
		}

		if (object->GetName() == name)
		{
			return object;
		}
	}

	return nullptr;
}

Array<WorldObject*> World::GetRootObjects() const
{
	Array<WorldObject*> rootObjects = {};

	for (uint32 i = 0; i < objects_.Count(); ++i)
	{
		WorldObject* object = objects_[i].get();

		if (!object)
		{
			continue;
		}

		if (!object->GetParent())
		{
			rootObjects.Add(object);
		}
	}

	return rootObjects;
}

uint32 World::GetObjectCount() const
{
	return objects_.Count();
}

void World::Exit(const int32 code)
{
	exitCode_ = code;
	Shutdown();
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

void World::Tick(const double deltaTime)
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