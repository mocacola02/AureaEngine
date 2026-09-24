#pragma once

#include "../WorldObject.h"


class WorldObject3D : public WorldObject
{
public:
	WorldObject3D() = default;
	explicit WorldObject3D(const Transform3D& worldTransform) : worldTransform_(worldTransform) {}

	//! Returns this object's local transform relative to this object's parent
	const Transform3D& GetLocalTransform() const;
	//! Sets this object's local transform relative to this object's parent
	void SetLocalTransform(const Transform3D& transform);

	//! Returns this object's world transform relative to the world origin
	const Transform3D& GetWorldTransform() const;
	//! Sets this object's world transform relative to the world origin
	void SetWorldTransform(const Transform3D& transform);

	//! Returns this object's local position relative to this object's parent
	const Vector3& GetLocalPosition() const;
	//! Sets this object's local position relative to this object's parent
	void SetLocalPosition(const Vector3& position);

	//! Returns this object's world position relative to the world origin
	const Vector3& GetWorldPosition() const;
	//! Sets this object's world position relative to the world origin
	void SetWorldPosition(const Vector3& position);

	//! Returns this object's local rotation relative to this object's parent
	const Quaternion& GetLocalRotation() const;
	//! Sets this object's local rotation relative to this object's parent
	void SetLocalRotation(const Quaternion& rotation);

	//! Returns this object's world rotation relative to the world origin
	const Quaternion& GetWorldRotation() const;
	//! Sets this object's world rotation relative to the world origin
	void SetWorldRotation(const Quaternion& rotation);

	//! Returns this object's local rotation in radians relative to this object's parent
	Vector3 GetLocalRotationEuler() const;
	//! Sets this object's local rotation in radians relative to this object's parent
	void SetLocalRotationEuler(const Vector3& eulerRadians);

	//! Returns this object's world rotation in radians relative to the world origin
	Vector3 GetWorldRotationEuler() const;
	//! Sets this object's world rotation in radians relative to the world origin
	void SetWorldRotationEuler(const Vector3& eulerRadians);

	//! Returns this object's local rotation in degrees relative to this object's parent
	Vector3 GetLocalRotationDegrees() const;
	//! Sets this object's local rotation in degrees relative to this object's parent
	void SetLocalRotationDegrees(const Vector3& eulerDegrees);

	//! Returns this object's world rotation in degrees relative to the world origin
	Vector3 GetWorldRotationDegrees() const;
	//! Sets this object's world rotation in degrees relative to the world origin
	void SetWorldRotationDegrees(const Vector3& eulerDegrees);

	//! Returns the scale of this object
	const Vector3& GetScale() const;
	//! Sets the scale of this object
	void SetLocalScale(const Vector3& scale);

	//! Returns the forward vector of this object
	Vector3 GetForward() const;
	//! Returns the right vector of this object
	Vector3 GetRight()	 const;
	//! Returns the up vector of this object
	Vector3 GetUp()		 const;

	//! Returns if this object is visible
	bool IsVisible() const;
	//! Sets the visibility of this object
	void SetVisibility(bool visible);

	//! Returns if this object is visible in the editor
	bool IsVisibleInEditor() const;
	//! Sets if this object is visible in the editor
	void SetEditorVisibility(const bool visible);

private:
	bool visible_		  = true;
	bool visibleInEditor_ = true;

	Transform3D worldTransform_;
};

