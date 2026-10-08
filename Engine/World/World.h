#pragma once

#include "WorldObject.h"

class World final : public Object
{
public:
	explicit World(Runtime* runtime) : Object(runtime), rootObject_(runtime) {}

	WorldObject* GetRootObject();
	const WorldObject* GetRootObject() const;

	Array<WorldObject*> GetWorldObjects();

	template<typename Type>
	Array<Type*> GetWorldObjectsOfType();

	void DestroyPendingObjects();

	bool IsPaused() const;

	template<typename Base, typename Derived>
	bool IsClassBasedOn() const;

protected:
	friend class Runtime;

	bool Initialize() override;
	void Tick(double deltaTime);
	void Shutdown() override;

	Array<WorldObject*> GetTickList(double deltaTime);

private:
	bool paused_ = false;

	WorldObject rootObject_;

	Runtime* runtime_ = nullptr;
};