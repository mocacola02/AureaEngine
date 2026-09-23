#pragma once

#include "../CoreInc.h"

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
	void Initialize();
	void PreStart();
	void Start();
	void PostStart();

	void Tick(double deltaTime);

	[[nodiscard]] bool HasStarted() const;

	[[nodiscard]] bool IsPendingDestroy() const;
	void Destroy();

	[[nodiscard]] bool IsTickable() const;
	void SetTickMode(const TickMode& tickMode);

	WorldObject*	   GetParent();
	[[nodiscard]] const WorldObject* GetParent() const;

	[[nodiscard]] const Array<WorldObject*>& GetChildren() const;

	void AddChild(WorldObject* object);
	void RemoveChild(WorldObject* object);

	[[nodiscard]] bool HasParent() const;
	[[nodiscard]] bool HasChildren() const;
	bool HasChild(const WorldObject* object) const;
	bool IsChildOf(const WorldObject* object) const;

	bool SetParent(WorldObject* parent, bool keepWorldTransform = true);
	void RemoveParent(bool keepWorldTransform = true);

	World* GetWorld();
	[[nodiscard]] const World* GetWorld() const;

protected:
	friend class World;

	bool started_		 = false;
	bool pendingDestroy_ = false;


	TickMode tickMode_ = TickMode::Inherit;

	uint32 ticksPerSecond_ = 0;

	double tickAccumlator_ = 0.0;

	WorldObject*		parent_ = nullptr;
	Array<WorldObject*> children_;

	World* world_ = nullptr;


	bool CanTick(double deltaTime);

	virtual void OnInitialize() {}
	virtual void OnPreStart()	{}
	virtual void OnStart()		{}
	virtual void OnPostStart()	{}

	virtual void OnTick(double deltaTime) {}

	virtual void OnDestroy() {}

	void SetWorld(World* world)
	{
		world_ = world;
	}
};