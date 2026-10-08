#pragma once

#include "Core.h"

class World;

enum class TickMode : uint8
{
	Inherit,
	Pausable,
	DuringPause,
	Always,
	Disabled
};

class WorldObject : public Object
{
public:
	explicit WorldObject(Runtime* runtime) : Object(runtime) {}

	//! Returns whether or not this WorldObject has started yet.
	bool HasStarted() const;
	//! Runs any internal behavior needed before allowed to start ticking and calls OnPreStart().
	virtual void PreStart();
	//! Runs any internal behavior needed, sets that the WorldObject can now tick, and calls OnStart().
	virtual void Start();
	//! Runs any internal behavior needed the first time the WorldObject ticks and calls OnPostStart().
	virtual void PostStart();

	//! Runs any internal behavior needed and calls OnTick().
	void Tick(double deltaTime);

	//! Returns whether or not this WorldObject is pending destruction.
	bool IsPendingDestroy() const;
	//! Sets this WorldObject to be pending destruction.
	void Destroy();

	//! Sets the tick mode of this WorldObject.
	void SetTickMode(const TickMode& tickMode);
	//! Returns the tick mode on this WorldObject.
	TickMode GetTickMode() const;

	//! Returns the root WorldObject of the world.
	WorldObject*	GetWorldRoot();
	//! Returns the root WorldObject of the world as a constant.
	const WorldObject* GetWorldRoot() const;
	//! Returns whether or not this WorldObject is the world root.
	bool IsWorldRoot() const;

	//! Returns an Object pointer registered to a given UUID.
	Object* GetObjectFromUUID(const UUID& uuid);

	//! Returns an array of WorldObject children of this WorldObject. If you want to include the "children's children", use GetDescendents().
	Array<WorldObject*> GetChildren();
	//! Returns an array of UUIDs of this WorldObject's children.
	Array<UUID> GetChildrenUUID() const;

	//! Returns an array of WorldObject descendents of this WorldObject, in the order of each direct child to furthest (any descendents without children)
	Array<WorldObject*> GetDescendents();
	//! Returns an array of UUIDs of this WorldObject's descendents.
	Array<UUID> GetDescendentsUUID();
	//! Returns an array of WorldObject ancestors of this WorldObject, in order of nearest ancestor (parent) to furthest (world root).
	Array<WorldObject*> GetAncestors();
	//! Returns an array of UUIDs of this WorldObject's ancestors.
	Array<UUID> GetAncestorsUUID();

	//! Returns whether or not this WorldObject has a parent
	bool HasParent() const;
	//! Returns a pointer to this WorldObject's parent
	WorldObject* GetParent();
	//! Returns the UUID of this WorldObject's parent
	UUID GetParentUUID();

	//! Returns whether or not this WorldObject has any children.
	bool HasChildren() const;
	//! Returns whether or not this WorldObject has a given WorldObject as a child.
	bool HasChild(const WorldObject* object) const;
	//! Returns whether or not this WorldObject is a child of a given WorldObject.
	bool IsChildOf(const WorldObject* object) const;

	//! Returns whether or not this WorldObject has a given WorldObject as a descendent.
	bool HasDescendent(WorldObject* object);
	//! Returns whether or not this WorldObject is a descendent of a given WorldObject.
	bool IsDescendentOf(WorldObject* object);

	//! Sets the parent of this WorldObject to a given WorldObject.
	//! Returns whether or not it was successful.
	bool SetParent(WorldObject* newParent);
	//! Removes the current parent and becomes a child of the World root.
	//! Returns whether or not it was successful.
	bool RemoveParent();

	//! Returns a pointer to the World.
	World* GetWorld();
	//! Returns a pointer to the World as a constant.
	const World* GetWorld() const;

protected:
	friend class World;

	//! Whether or not this WorldObject has started.
	bool started_		   = false;
	//! Whether or not this WorldObject is pending destruction.
	bool pendingDestroy_   = false;

	//! Tick mode of this WorldObject.
	TickMode tickMode_ = TickMode::Inherit;
	//! Tick rate of this WorldObject.
	//! Example: If ticksPerSeconds_ = 20, this WorldObject will only tick
	//! 20 times per second instead of each engine tick.
	uint32	 ticksPerSecond_ = 0;
	//! Accumulated time since last tick, used to determine if this WorldObject
	//! should tick if ticksPerSecond_ > 0.
	double	 tickAccumlator_ = 0.0;

	//! Number of times this WorldObject has ticked during its lifetime.
	uint64 tickCount_ = 0;
	//! How long this WorldObject has existed in seconds.
	double lifetime_ = 0.0;

	//! UUID of this WorldObject's parent.
	//! If UUID = UUID::None(), then this WorldObject is a root object.
	UUID parent_ = UUID::None();
	//! Array of UUIDs of this WorldObject's children.
	Array<UUID> children_;

	//! Pointer to the owning World.
	World* world_ = nullptr;

	//! Called after the WorldObject is constructed, runs internal behavior
	//! for initializing this WorldObject and calls OnInitialize().
	bool Initialize() override;

	//! Sets the world pointer to a given World pointer.
	bool SetWorld(World* world);

	//! Adds a given WorldObject to this WorldObject's children array.
	//! This is equivalent to calling AddChildUUID(object->GetUUID());
	bool AddChild(const WorldObject* object);
	//! Adds a given UUID to this WorldObject's children array.
	bool AddChildUUID(const UUID& uuid);

	//! Removes a given WorldObject from this WorldObject's children array.
	//! This is equivalent to calling RemoveChildUUID(object->GetUUID());
	bool RemoveChild(const WorldObject* object);
	//! Removes a given UUID from this WorldObject's children array.
	bool RemoveChildUUID(const UUID& uuid);

	//! Returns whether or not this WorldObject should currently tick.
	//! This returns false if the WorldObject has not started yet.
	//! This function also handles tick mode inheritance if tick mode is Inherit.
	//! This function handles tick accumulation and ticks per second evaluation as well.
	bool ShouldTick(double deltaTime);

	//! Called after internal initialize behavior runs. Intended to be extended in child classes.
	virtual void OnInitialize() {}
	//! Called after internal pre-start behavior runs. Intended to be extended in child classes.
	virtual void OnPreStart()	{}
	//! Called after internal start behavior runs. Intended to be extended in child classes.
	virtual void OnStart()		{}
	//! Called after internal post-start behavior runs. Intended to be extended in child classes.
	virtual void OnPostStart()	{}
	//! Called after internal tick behavior runs. Intended to be extended in child classes.
	virtual void OnTick(double deltaTime) {}
	//! Called right before the WorldObject is deleted from memory. Intended to be extended in child classes.
	virtual void OnDestroy() {}
};