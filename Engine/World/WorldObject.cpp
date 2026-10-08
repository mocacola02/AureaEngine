#include "WorldObject.h"
#include "World.h"

bool WorldObject::HasStarted() const
{
	return started_;
}

void WorldObject::PreStart()
{
	OnPreStart();
}

void WorldObject::Start()
{
	started_ = true;
	OnStart();
}

void WorldObject::PostStart()
{
	OnPostStart();
}

void WorldObject::Tick(const double deltaTime)
{
	if (tickCount_ == 0)
	{
		PostStart();
	}

	lifetime_ += deltaTime;
	++tickCount_;

	OnTick(deltaTime);
}

bool WorldObject::IsPendingDestroy() const
{
	return pendingDestroy_;
}

void WorldObject::Destroy()
{
	pendingDestroy_ = true;
}

void WorldObject::SetTickMode(const TickMode& tickMode)
{
	tickMode_ = tickMode;
}

TickMode WorldObject::GetTickMode() const
{
	return tickMode_;
}

WorldObject* WorldObject::GetWorldRoot()
{
	return GetWorld()->GetRootObject();
}

const WorldObject* WorldObject::GetWorldRoot() const
{
	return GetWorld()->GetRootObject();
}

bool WorldObject::IsWorldRoot() const
{
	return GetWorldRoot() == this;
}

Object* WorldObject::GetObjectFromUUID(const UUID& uuid)
{
	return GetRuntime()->GetUUIDManager().GetObject(uuid);
}

Array<UUID> WorldObject::GetChildrenUUID() const
{
	return children_;
}

Array<WorldObject*> WorldObject::GetChildren()
{
	Array<WorldObject*> children;

	for (const UUID uuid : GetChildrenUUID())
	{
		WorldObject* object = static_cast<WorldObject*>(GetObjectFromUUID(uuid));

		if (!object)
		{
			WARN(String("Could not find child with UUID ") + uuid.Value() + ", removing from children array.");
			continue;
		}

		children.Add(object);
	}

	return children;
}

Array<WorldObject*> WorldObject::GetDescendents()
{
	Array<WorldObject*> descendents;
	Array<WorldObject*> stack;

	for (const UUID uuid : GetChildrenUUID())
	{
		if (WorldObject* object = static_cast<WorldObject*>(GetObjectFromUUID(uuid)); !object)
		{
			WARN(String("Could not find child with UUID ") + uuid.Value() + ". Maybe it's been destroyed?");
		}
		else
		{
			stack.PushBack(object);
		}
	}

	while (!stack.IsEmpty())
	{
		WorldObject* current = stack.PopBack();
		descendents.PushBack(current);

		for (const UUID uuid : current->GetChildrenUUID())
		{
			if (WorldObject* child = static_cast<WorldObject*>(GetObjectFromUUID(uuid)); !child)
			{
				WARN(String("Could not find child with UUID ") + uuid.Value() + ". Maybe it's been destroyed?");
			}
			else
			{
				stack.PushBack(child);
			}
		}
	}

	return descendents;
}

Array<UUID> WorldObject::GetDescendentsUUID()
{
	Array<UUID> descendents;
	Array<UUID> stack;

	for (const UUID uuid : GetChildrenUUID())
	{
		if (!uuid.IsValid())
		{
			WARN(String("Skipping child with invalid UUID"));
		}
		else
		{
			stack.PushBack(uuid);
		}
	}

	while (!stack.IsEmpty())
	{
		UUID current = stack.PopBack();
		descendents.PushBack(current);

		for (const WorldObject* currentObj = static_cast<WorldObject*>(GetObjectFromUUID(current));
			 const UUID uuid : currentObj->GetChildrenUUID()
		)
		{
			if (!uuid.IsValid())
			{
				WARN(String("Skipping descendent with invalid UUID"));
			}
			else
			{
				stack.PushBack(uuid);
			}
		}
	}

	return descendents;
}

Array<WorldObject *> WorldObject::GetAncestors()
{
	Array<WorldObject*> ancestors;
	WorldObject* current = GetParent();

	while (current != nullptr)
	{
		ancestors.PushBack(current);

		current = current->GetParent();
	}

	return ancestors;
}

Array<UUID> WorldObject::GetAncestorsUUID()
{
	Array<UUID> ancestors;
	const WorldObject* current = GetParent();

	while (current != nullptr)
	{
		if (const UUID newUUID = current->GetUUID(); !newUUID.IsValid())
		{
			WARN("Skipping ancestor with invalid UUID.");
		}
		else
		{
			ancestors.PushBack(newUUID);
		}
	}

	return ancestors;
}

bool WorldObject::HasParent() const
{
	return parent_.IsValid();
}

WorldObject* WorldObject::GetParent()
{
	return static_cast<WorldObject*>(GetRuntime()->GetUUIDManager().GetObject(parent_));
}

UUID WorldObject::GetParentUUID()
{
	return parent_;
}

bool WorldObject::HasChildren() const
{
	return !children_.IsEmpty();
}

bool WorldObject::HasChild(const WorldObject* object) const
{
	return children_.Contains(object->GetUUID());
}

bool WorldObject::IsChildOf(const WorldObject* object) const
{
	return parent_ == object->GetUUID();
}

bool WorldObject::HasDescendent(WorldObject* object)
{
	if (!object)
	{
		WARN("Cannot search using an invalid object pointer!");
		return false;
	}

	const Array<WorldObject*> descendents = GetDescendents();

	return descendents.Contains(object);
}

bool WorldObject::IsDescendentOf(WorldObject* object)
{
	if (!object)
	{
		WARN("Cannot search using an invalid object pointer!");
		return false;
	}

	const Array<WorldObject*> ancestors = GetAncestors();

	return ancestors.Contains(object);
}

bool WorldObject::SetParent(WorldObject* newParent)
{
	if (!newParent)
	{
		ERROR("Cannot set parent to invalid object pointer!");
		return false;
	}

	if (!newParent->GetUUID().IsValid())
	{
		ERROR("Cannot set parent to parent with invalid UUID.");
		return false;
	}

	if (HasParent())
	{
		if (!GetParent()->RemoveChild(this))
		{
			ERROR("Failed to remove self from parent's children.");
			return false;
		}

		parent_ = UUID::None();
	}

	if (!newParent->AddChild(this))
	{
		ERROR("Failed to add self to new parent's children.");
		return false;
	}

	parent_ = newParent->GetUUID();

	return HasParent();
}

bool WorldObject::RemoveParent()
{
	return SetParent(GetWorldRoot());
}

World* WorldObject::GetWorld()
{
	return world_;
}

const World* WorldObject::GetWorld() const
{
	return world_;
}

bool WorldObject::Initialize()
{
	world_ = &GetRuntime()->GetWorld();

	return world_;
}

bool WorldObject::SetWorld(World* world)
{
	if (!world)
	{
		ERROR("Cannot set world with invalid pointer!");
		return false;
	}

	world_ = world;

	return world_ != nullptr;
}

bool WorldObject::AddChild(const WorldObject* object)
{
	if (!object)
	{
		ERROR("Cannot add child using invalid object pointer!");
		return false;
	}

	return AddChildUUID(object->GetUUID());
}

bool WorldObject::AddChildUUID(const UUID &uuid)
{
	if (!uuid.IsValid())
	{
		ERROR("Cannot add child with invalid UUID!");
		return false;
	}

	children_.Add(uuid);

	return children_.Contains(uuid);
}

bool WorldObject::RemoveChild(const WorldObject *object)
{
	if (!object)
	{
		ERROR("Cannot remove child using invalid object pointer!");
		return false;
	}

	return RemoveChildUUID(object->GetUUID());
}

bool WorldObject::RemoveChildUUID(const UUID &uuid)
{
	if (!uuid.IsValid())
	{
		ERROR("Cannot remove child with invalid UUID!");
		return false;
	}

	children_.Remove(uuid);

	return !children_.Contains(uuid);
}

bool WorldObject::ShouldTick(const double deltaTime)
{
	if (!HasStarted())
	{
		return false;
	}

	bool canTickThisFrame = false;

	TickMode tickMode = GetTickMode();

	if (tickMode == TickMode::Inherit)
	{
		for (const WorldObject* object : GetAncestors())
		{
			if (const TickMode ancTM = object->GetTickMode(); ancTM != TickMode::Inherit)
			{
				tickMode = ancTM;
				break;
			}
		}
	}

	switch(tickMode)
	{
		case TickMode::Pausable:
		{
			canTickThisFrame = !GetWorld()->IsPaused();
			break;
		}
		case TickMode::DuringPause:
		{
			canTickThisFrame = GetWorld()->IsPaused();
		}
		case TickMode::Always:
		{
			canTickThisFrame = true;
		}
		case TickMode::Inherit:
		case TickMode::Disabled:
		default:
		{
			canTickThisFrame = false;
		}
	}

	if (canTickThisFrame && ticksPerSecond_ > 0)
	{
		tickAccumlator_ += deltaTime;

		const double tpsMs = 1.0 / ticksPerSecond_;
		canTickThisFrame = Math::IsGreaterThanOrEqualApprox(tickAccumlator_, tpsMs);
	}

	if (canTickThisFrame)
	{
		tickAccumlator_ = 0.0;
	}

	return canTickThisFrame;
}