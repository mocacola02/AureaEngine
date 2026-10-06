#include "WorldObject.h"
#include "World.h"

bool WorldObject::Initialize()
{
	world_ = &GetRuntime()->GetWorld();

	return world_;
}

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

bool WorldObject::CanTickThisFrame() const
{
	return canTickThisFrame_;
}

bool WorldObject::ShouldTick(const double deltaTime)
{
	canTickThisFrame_ = false;

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
			canTickThisFrame_ = !GetWorld()->IsPaused();
			break;
		}
		case TickMode::DuringPause:
		{
			canTickThisFrame_ = GetWorld()->IsPaused();
		}
		case TickMode::Always:
		{
			canTickThisFrame_ = true;
		}
		case TickMode::Inherit:
		case TickMode::Disabled:
		default:
		{
			canTickThisFrame_ = false;
		}
	}

	if (canTickThisFrame_ && ticksPerSecond_ > 0)
	{
		AccumulateTick(deltaTime);

		const double tpsMs = 1.0 / ticksPerSecond_;
		canTickThisFrame_ = Math::IsGreaterThanOrEqualApprox(tickAccumlator_, tpsMs);
	}

	if (canTickThisFrame_)
	{
		tickAccumlator_ = 0.0;
	}

	return canTickThisFrame_;
}

void WorldObject::SetTickMode(const TickMode& tickMode)
{
	tickMode_ = tickMode;
}

TickMode WorldObject::GetTickMode() const
{
	return tickMode_;
}

WorldObject* WorldObject::GetParent()
{
	return GetWorld()->GetRuntime()->GetUUIDManager().GetObject(parent_);
}

const WorldObject* WorldObject::GetParent() const
{
	return parent_;
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

Object* WorldObject::GetObjectFromUUID(const uint32 uuid)
{
	return GetWorld()->GetRuntime()->GetUUIDManager().GetObject(uuid);
}

const Object* WorldObject::GetObjectFromUUID(const uint32 uuid) const
{
	return GetWorld()->GetRuntime()->GetUUIDManager().GetObject(uuid);
}

Array<uint32> WorldObject::GetChildrenUUID() const
{
	return children_;
}

Array<WorldObject*> WorldObject::GetChildren()
{
	Array<WorldObject*> children;

	for (const uint32 uuid : GetChildrenUUID())
	{
		WorldObject* object = static_cast<WorldObject*>(GetObjectFromUUID(uuid));

		if (!object)
		{
			WARN(String("Could not find child with UUID ") + uuid + ", removing from children array.");
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

	for (const uint32 uuid : GetChildrenUUID())
	{
		if (WorldObject* object = static_cast<WorldObject*>(GetObjectFromUUID(uuid)); !object)
		{
			WARN(String("Could not find child with UUID ") + uuid + ". Maybe it's been destroyed?");
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

		for (const uint32 uuid : current->GetChildrenUUID())
		{
			if (WorldObject* child = static_cast<WorldObject*>(GetObjectFromUUID(uuid)); !child)
			{
				WARN(String("Could not find child with UUID ") + uuid + ". Maybe it's been destroyed?");
			}
			else
			{
				stack.PushBack(child);
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

bool WorldObject::HasParent() const
{
	return parent_ != 0;
}