#pragma once

#include "../CoreInc.h"
#include "../EngineLoop.h"

#include "WorldObject.h"


class World final : public EngineLoop
{
public:
	void Start();
	void Tick();
	void Shutdown();

	template<typename T, typename... Args>
	T* SpawnObject(Args&&... args);

	bool DestroyObject(WorldObject* object);
	void DestroyPendingObjects();

	Array<unique_ptr<WorldObject>>&		  GetObjects();
	const Array<unique_ptr<WorldObject>>& GetObjects() const;

	WorldObject*	   FindObjectByID(const uint32 id);
	const WorldObject* FindObjectByID(const uint32 id) const;

	WorldObject*	   FindObjectByName(const Name& name);
	const WorldObject* FindObjectByName(const Name& name) const;

	Array<WorldObject*>& GetRootObjects() const;

	uint32 GetObjectCount() const;

	bool HasStarted() const;

private:
	bool started_ = false;
};