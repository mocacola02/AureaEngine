//===================================================
// Transform3D.h
// Author: Moca 9/16/2026
// Defines a 3D transform type that tracks
// position, rotation, and scale.
//===================================================
#pragma once

#include "Matrix4.h"
#include "Quaternion.h"

//! Defines a 3D transform type that tracks position, rotation, and scale with double precision.
struct Transform3D
{
	Vector3		position;
	Quaternion	rotation;
	Vector3		scale;

	[[nodiscard]] constexpr Matrix4 GetMatrix() const
	{
		return Matrix4::Translation(position) * Matrix4::Rotation(rotation) * Matrix4::Scale(scale);
	}

	[[nodiscard]] constexpr Vector3 GetForward() const
	{
		return rotation.Rotate(Vector3::Forward());
	}

	[[nodiscard]] constexpr Vector3 GetRight() const
	{
		return rotation.Rotate(Vector3::Right());
	}

	[[nodiscard]] constexpr Vector3 GetUp() const
	{
		return rotation.Rotate(Vector3::Up());
	}

	constexpr void Reset()
	{
		position = Vector3::Zero();
		rotation = Quaternion::Identity();
		scale	 = Vector3::Zero();
	}

	static Transform3D Combine(const Transform3D& parent, const Transform3D& local)
	{
		Transform3D result;

		result.scale = parent.scale * local.scale;

		result.rotation = parent.rotation * local.rotation;

		const Vector3 scaledPosition = local.position * parent.scale;

		result.position = parent.position + parent.rotation.Rotate(scaledPosition);

		return result;
	}

	static constexpr Transform3D MakeRelative(const Transform3D& world, const Transform3D& parent)
	{
		Transform3D result;

		const Quaternion inverseRotation = parent.rotation.Inverse();

		result.rotation = inverseRotation * world.rotation;

		result.scale = {
			parent.scale.x != 0.0 ? world.scale.x / parent.scale.x : 0.0,
			parent.scale.y != 0.0 ? world.scale.y / parent.scale.y : 0.0,
			parent.scale.z != 0.0 ? world.scale.z / parent.scale.z : 0.0
		};

		const Vector3 relativePosition = inverseRotation.Rotate(world.position - parent.position);

		result.position = {
			parent.scale.x != 0.0 ? relativePosition.x * parent.scale.x : 0.0,
			parent.scale.y != 0.0 ? relativePosition.y * parent.scale.y : 0.0,
			parent.scale.z != 0.0 ? relativePosition.z * parent.scale.z : 0.0
		};

		return result;
	}

	//! Returns whether or not this Transform3D is equal to another given Transform3D.
	constexpr bool operator==(const Transform3D& right) const
	{
		return position == right.position && rotation == right.rotation && scale == right.scale;
	}

	//! Returns whether or not this Transform3D is not equal to another given Transform3D.
	constexpr bool operator!=(const Transform3D& right) const
	{
		return !(*this == right);
	}
};