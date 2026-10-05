#pragma once

#include "EngineLoop.h"
#include "../../Object/Inc/WorldObject.h"

#include <Core.h>

class World final : public EngineLoop
{
public:
	explicit World(Runtime* runtime) : EngineLoop(runtime), rootObject_(runtime) {}

	Array<WorldObject*> GetWorldObjects();

	template<typename Type>
	Array<Type*> GetWorldObjectsOfType();

	template<typename Base, typename Derived>
	bool IsBasedOn() const noexcept;

	void DestroyPendingObjects();

protected:
	friend class Runtime;

	bool Initialize() override;
	void Tick(double deltaTime) override;
	void Shutdown() override;

	Array<WorldObject*> GetTickList(double deltaTime);

private:
	bool paused_ = false;

	WorldObject rootObject_;

	Runtime* runtime_ = nullptr;
};