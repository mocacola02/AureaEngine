#pragma once

#include "EngineLoop.h"

#include <Core.h>


class WorldObject;
class Camera3D;

class World final : public EngineLoop
{
public:
	bool DestroyObject(WorldObject* object);
	void DestroyPendingObjects();

	Array<WorldObject*>& GetObjects();
	const Array<WorldObject*>& GetObjects() const;

	WorldObject* FindObjectByID(uint32 id);
	const WorldObject* FindObjectByID(uint32 id) const;

	WorldObject*		FindObjectByName(const Name& name);
	const WorldObject* FindObjectByName(const Name& name) const;

	Array<WorldObject*> GetRootObjects() const;

	static Array<WorldObject*> GetTickableChildren(const WorldObject* root, bool rootShouldTick, double deltaTime);

	uint32 GetObjectCount() const;

	bool IsPaused() const;

	bool SetCamera3D(Camera3D* camera);

	void Exit(int32 code) override;

protected:
	friend class Runtime;

	bool Initialize() override;

	void Tick(double deltaTime) override;

	void Shutdown() override;

private:
	//! Tracks if this EngineLoop is running or not.
	bool running_ = false;
	//! Is the loop paused?
	bool paused_ = false;

	//! Code to return to the Application when exiting. Set via Exit()
	int32 exitCode_ = 0;

	Array<WorldObject*> objects_;

	Camera3D* camera3D_ = nullptr;
};