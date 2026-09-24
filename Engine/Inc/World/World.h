#pragma once

#include "../CoreInc.h"
#include "../EngineLoop.h"

class WorldObject;
class Camera3D;

class World final : public EngineLoop
{
public:
	bool DestroyObject(WorldObject* object);
	void DestroyPendingObjects();

	Array<WorldObject*>& GetObjects();
	[[nodiscard]] const Array<WorldObject*>& GetObjects() const;

	WorldObject* FindObjectByID(uint32 id);
	[[nodiscard]] const WorldObject* FindObjectByID(uint32 id) const;

	WorldObject*		FindObjectByName(const Name& name);
	[[nodiscard]] const WorldObject* FindObjectByName(const Name& name) const;

	[[nodiscard]] Array<WorldObject*> GetRootObjects() const;

	static Array<WorldObject*> GetTickableChildren(const WorldObject* root, bool rootShouldTick, double deltaTime);

	[[nodiscard]] uint32 GetObjectCount() const;

	[[nodiscard]] bool IsPaused() const;

	bool SetCamera3D(Camera3D* camera);

protected:
	void Exit(int32 code) override;

	bool Initialize() override;

	void Tick(double deltaTime) override;

	void Shutdown() override;

private:
	bool paused_ = false;

	Array<WorldObject*> objects_;

	Camera3D* camera3D_ = nullptr;

	template<typename T, typename... Args>
	T* SpawnObject(Args&&... args);
};