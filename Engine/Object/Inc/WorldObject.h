#pragma once

#include <Core.h>

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
	explicit WorldObject(Runtime* runtime) : Object(runtime);

	bool Initialize() override;

	void PreStart();
	void Start();
	void PostStart();
	bool HasStarted() const;

	void Tick(double deltaTime);

	bool IsPendingDestroy() const;

	void Destroy();

	bool ShouldTick(bool parentShouldTick, double deltaTime);
	void SetTickMode(const TickMode& tickMode);
	TickMode GetTickMode() const;

	WorldObject*	   GetParent();
	const WorldObject* GetParent() const;

	WorldObject*	GetRoot();
	const WorldObject* GetRoot() const;
	bool IsRoot() const;

	const Array<WorldObject*>& GetChildren() const;

	bool HasParent() const;
	bool HasChildren() const;
	bool HasChild(WorldObject *object) const;
	bool IsChildOf(const WorldObject* object) const;

	bool HasDescendent(WorldObject* object) const;
	bool IsDescendentOf(const WorldObject* object) const;

	bool SetParent(WorldObject* parent);
	void RemoveParent();

	World* GetWorld();
	const World* GetWorld() const;

protected:
	friend class World;

	bool started_		   = false;
	bool pendingDestroy_   = false;
	bool canTickThisFrame_ = false;

	TickMode tickMode_ = TickMode::Inherit;
	uint32	 ticksPerSecond_ = 0;
	double	 tickAccumlator_ = 0.0;

	uint64 tickCount_ = 0;
	double lifetime_ = 0.0;

	WorldObject*		parent_ = nullptr;
	WorldObject*		root_	= nullptr;
	Array<WorldObject*> children_;

	World* world_ = nullptr;


	bool AccumulateTick(double deltaTime);

	void SetWorld(World* world);

	void AddChild(WorldObject* object);
	void RemoveChild(WorldObject* object);

	void UpdateRoot();

	virtual void OnInitialize() {}
	virtual void OnPreStart()	{}
	virtual void OnStart()		{}
	virtual void OnPostStart()	{}

	virtual void OnTick(double deltaTime) {}

	virtual void OnDestroy() {}
};