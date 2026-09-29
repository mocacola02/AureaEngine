#pragma once

#include "WorldObject3D.h"

//! Camera object used to view/render the 3D world.
class Camera3D : public WorldObject3D
{
public:
	//! Returns whether or not this camera is the current World camera.
	[[nodiscard]] bool IsCurrent() const;
	//! Makes this camera the current World camera.
	void MakeCurrent();

	//! Returns the FOV of this camera.
	[[nodiscard]] float GetFOV() const;
	//! Sets the FOV of this camera.
	void SetFOV(float fov);

	//! Returns the near clip plane of this camera.
	[[nodiscard]] float GetNearClipPlane() const;
	//! Sets the near clip plane of this camera.
	void SetNearClipPlane(float nearClipPlane);

	//! Returns the far clip plane of this camera.
	[[nodiscard]] float GetFarClipPlane() const;
	//! Sets the far clip plane of this camera.
	void SetFarClipPlane(float farClipPlane);


private:
	//! Is this camera the current World camera.
	bool current_ = false;

	//! FOV angle of this camera.
	float fov_ = 90.0f;
	//! Near clip plane distance, determines the closest point this camera can view.
	float nearClipPlane_ = 0.1f;
	//! Far clip plane distance, determines the furthest point this camera can view.
	float farClipPlane_  = 4000.0f;
};