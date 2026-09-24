#include "../../../Inc/World/3D/Camera3D.h"
#include "../../../Inc/World/World.h"

bool Camera3D::IsCurrent() const
{
	return current_;
}

void Camera3D::MakeCurrent()
{
	current_ = world_->SetCamera3D(this);
}

float Camera3D::GetFOV() const
{
	return fov_;
}

void Camera3D::SetFOV(const float fov)
{
	fov_ = Math::Clamp(fov, 1.0f, 10000.0f);;
}

float Camera3D::GetNearClipPlane() const
{
	return nearClipPlane_;
}

void Camera3D::SetNearClipPlane(const float nearClipPlane)
{
	nearClipPlane_ = Math::Clamp(nearClipPlane, 0.001f, farClipPlane_ - 0.01f);
}

float Camera3D::GetFarClipPlane() const
{
	return farClipPlane_;
}

void Camera3D::SetFarClipPlane(const float farClipPlane)
{
	farClipPlane_ = Math::Clamp(farClipPlane, nearClipPlane_ + 0.01f, 100000.0f);
}