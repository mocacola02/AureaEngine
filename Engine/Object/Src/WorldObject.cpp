#include "../../Inc/World/WorldObject.h"
#include "Inc/World/World.h"

void WorldObject::Initialize()
{
	LOG(String("Initializing WorldObject: ") + GetName().ToString());

	if (tickMode_ == TickMode::Inherit && GetRoot() == this)
	{
		// We have nothing to inherit from, so let's be pausable.
		SetTickMode(TickMode::Pausable);
	}

	OnInitialize();
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
	++tickCount_;
	lifetime_ += deltaTime;

	OnTick(deltaTime);
}

bool WorldObject::HasStarted() const
{
	return started_;
}

bool WorldObject::IsPendingDestroy() const
{
	return pendingDestroy_;
}

void WorldObject::Destroy()
{
	pendingDestroy_ = true;
}

bool WorldObject::ShouldTick(const bool parentShouldTick, const double deltaTime)
{
	if (!HasStarted() || IsPendingDestroy())
	{
		return false;
	}

	bool validMode = false;

	switch (tickMode_)
	{
		case TickMode::Inherit:
		{
			validMode = parentShouldTick;
			break;
		}
		case TickMode::Pausable:
		{
			validMode = !world_->IsPaused();
			break;
		}
		case TickMode::DuringPause:
		{
			validMode = world_->IsPaused();
			break;
		}
		case TickMode::Always:
		{
			validMode = true;
			break;
		}
		case TickMode::Disabled:
		default:
		{
			validMode = false;
			break;
		}
	}

	if (ticksPerSecond_ > 0 && validMode)
	{
		return AccumulateTick(deltaTime);
	}

	return validMode;
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
	return parent_;
}

const WorldObject* WorldObject::GetParent() const
{
	return parent_;
}

WorldObject* WorldObject::GetRoot()
{
	return root_;
}

const WorldObject* WorldObject::GetRoot() const
{
	return root_;
}

bool WorldObject::IsRoot() const
{
	return !HasParent();
}

const Array<WorldObject*>& WorldObject::GetChildren() const
{
	return children_;
}

bool WorldObject::HasParent() const
{
	return parent_ != nullptr;
}

bool WorldObject::HasChildren() const
{
	return !children_.IsEmpty();
}

bool WorldObject::HasChild(WorldObject* object) const
{
	return children_.Contains(object);
}

bool WorldObject::IsChildOf(const WorldObject* object) const
{
	return parent_ == object;
}

bool WorldObject::HasDescendent(WorldObject* object) const
{
	if (!object)
	{
		return false;
	}

	for (const WorldObject* child : children_)
	{
		if (child == object || child->HasDescendent(object))
		{
			return true;
		}
	}

	return false;
}

bool WorldObject::IsDescendentOf(const WorldObject* object) const
{
	const WorldObject* current = GetParent();

	while (current)
	{
		if (current == object)
		{
			return true;
		}

		current = current->GetParent();
	}

	return false;
}

bool WorldObject::SetParent(WorldObject* parent)
{
	if (!parent)
	{
		return false;
	}

	if (parent == this)
	{
		return false;
	}

	if (HasDescendent(parent))
	{
		return false;
	}

	if (parent == parent_)
	{
		return true;
	}

	if (HasParent())
	{
		parent_->RemoveChild(this);
	}

	parent_ = parent;
	parent_->AddChild(this);

	UpdateRoot();

	return true;
}

void WorldObject::RemoveParent()
{
	parent_->RemoveChild(this);
	parent_ = nullptr;

	UpdateRoot();
}

World* WorldObject::GetWorld()
{
	return world_;
}

const World* WorldObject::GetWorld() const
{
	return world_;
}

bool WorldObject::AccumulateTick(const double deltaTime)
{
	const double timePerTick = 1.0 / ticksPerSecond_;

	if (deltaTime >= timePerTick)
	{
		tickAccumlator_ = 0.0;
		return true;
	}

	tickAccumlator_ += deltaTime;

	if (tickAccumlator_ >= timePerTick)
	{
		tickAccumlator_ = 0.0;
		return true;
	}

	return false;
}

void WorldObject::SetWorld(World* world)
{
	world_ = world;
}

void WorldObject::AddChild(WorldObject* object)
{
	children_.Add(object);
}

void WorldObject::RemoveChild(WorldObject* object)
{
	children_.Remove(object);
}

void WorldObject::UpdateRoot()
{
	WorldObject* current = this;

	while (current->HasParent())
	{
		current = current->GetParent();
	}

	root_ = current;
}
