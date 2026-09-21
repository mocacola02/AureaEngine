#pragma once

#include "../CoreInc.h"
#include "../EngineLoop.h"

class WorldObject;

class World final : public EngineLoop
{
public:
	bool DestroyObject(WorldObject* object);
	void DestroyPendingObjects();

	Array<unique_ptr<WorldObject>>&		  GetObjects();
	[[nodiscard]] const Array<unique_ptr<WorldObject>>& GetObjects() const;

	WorldObject*		FindObjectByID(uint32 id);
	[[nodiscard]] const WorldObject* FindObjectByID(uint32 id) const;

	WorldObject*		FindObjectByName(const Name& name);
	[[nodiscard]] const WorldObject* FindObjectByName(const Name& name) const;

	[[nodiscard]] Array<WorldObject*>& GetRootObjects() const;

	[[nodiscard]] uint32 GetObjectCount() const;

protected:
	[[nodiscard]] bool IsRunning() const override;

	void Exit(int32 code) override;

	bool Initialize() override;

	void Tick(double deltaTime) override;

	void Shutdown() override;

private:
	Array<unique_ptr<WorldObject>> objects_;

	template<typename T, typename... Args>
	T* SpawnObject(Args&&... args);
};