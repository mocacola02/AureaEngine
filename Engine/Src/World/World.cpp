#include "../../Inc/World/World.h"
#include "../../Inc/World/WorldObject.h"
#include "Inc/World/3D/Camera3D.h"

// TODO: Implement this for real
template<typename T, typename... Args>
T* World::SpawnObject(Args&&... args)
{
	unique_ptr<T> object = make_unique<T>(Forward<Args>(args)...);

	T* objectPtr = object.get();

	objectPtr->Initialize();

	return nullptr;
}

bool World::DestroyObject(WorldObject* object)
{
	if (!object)
	{
		return false;
	}

	bool found = false;

	for (const WorldObject* existing : objects_)
	{
		if (existing == object)
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
	// We'll destroy objects from the "bottom up."
	for (uint32 i = objects_.Count(); i > 0; --i)
	{
		const uint32 index = i - 1;

		WorldObject* object = objects_[index];

		if (!object)
		{
			objects_.RemoveAt(index);
			continue;
		}

		if (!object->IsPendingDestroy())
		{
			continue;
		}

		object->RemoveParent();

		while (!object->GetChildren().IsEmpty())
		{
			WorldObject* child = object->GetChildren().Last();

			if (!child)
			{
				break;
			}

			child->RemoveParent();
		}

		objects_.RemoveAt(index);
	}
}

Array<WorldObject*>& World::GetObjects()
{
	return objects_;
}

const Array<WorldObject*>& World::GetObjects() const
{
	return objects_;
}

WorldObject* World::FindObjectByID(const uint32 id)
{
	uint32 index = 0;

	for (WorldObject* object : objects_)
	{
		if (!object)
		{
			objects_.RemoveAt(index);
			++index;
			continue;
		}

		if (object->GetID() == id)
		{
			return object;
		}

		++index;
	}

	return nullptr;
}

const WorldObject* World::FindObjectByID(const uint32 id) const
{
	for (const WorldObject* object : objects_)
	{
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
	uint32 index = 0;

	for (WorldObject* object : objects_)
	{
		if (!object)
		{
			objects_.RemoveAt(index);
			++index;
			continue;
		}

		if (object->GetName() == name)
		{
			return object;
		}

		++index;
	}

	return nullptr;
}

const WorldObject* World::FindObjectByName(const Name &name) const
{
	for (const WorldObject* object : objects_)
	{
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

	for (WorldObject* object : objects_)
	{
		if (!object)
		{
			continue;
		}

		if (!object->HasParent())
		{
			rootObjects.Add(object);
		}
	}

	return rootObjects;
}

// CLEANUP: This all feels very messy
Array<WorldObject*> World::GetTickableChildren(const WorldObject* root, const bool rootShouldTick, const double deltaTime)
{
	Array<WorldObject*> tickableChildren = {};

	for (WorldObject* child : root->GetChildren())
	{
		const bool childShouldTick = child->ShouldTick(rootShouldTick, deltaTime);

		if (childShouldTick)
		{
			tickableChildren.Add(child);
		}

		if (Array<WorldObject*> tickableChildrenChildren = GetTickableChildren(child, childShouldTick, deltaTime);
			!tickableChildrenChildren.IsEmpty()
		)
		{
			tickableChildren.Combine(tickableChildrenChildren);
		}
	}

	return tickableChildren;
}

uint32 World::GetObjectCount() const
{
	return objects_.Count();
}

bool World::IsPaused() const
{
	return paused_;
}

bool World::SetCamera3D(Camera3D* camera)
{
	if (camera && !camera->IsPendingDestroy())
	{
		camera3D_ = camera;
		return true;
	}

	return false;
}

void World::Exit(const int32 code)
{
	exitCode_ = code;
	Shutdown();
}

bool World::Initialize()
{
	for (WorldObject* object : objects_)
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

	Array<WorldObject*> tickList;

	for (WorldObject* root : GetRootObjects())
	{
		const bool shouldRootTick = root->ShouldTick(true, deltaTime);

		if (shouldRootTick)
		{
			tickList.Add(root);
		}

		if (const Array<WorldObject*> tickableObjects = GetTickableChildren(root, shouldRootTick, deltaTime);
			!tickableObjects.IsEmpty()
		)
		{
			tickList.Combine(tickableObjects);
		}
	}

	for (WorldObject* object : tickList)
	{
		object->Tick(deltaTime);
	}

	DestroyPendingObjects();
}

void World::Shutdown()
{
	for (WorldObject* object : objects_)
	{
		if (!object)
		{
			continue;
		}

		object->RemoveParent();
	}

	for (WorldObject* object : objects_)
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