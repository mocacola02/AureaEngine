#pragma once

#include "Vector3.h"
#include "Vector4.h"

//! Quaternion type with double precision. Used in Transform3D. For float precision, see QuaternionF.
struct Quaternion
{
	Vector4 q = Vector4::Zero();

	constexpr Quaternion() = default;

	constexpr Quaternion(const double w, const double x, const double y, const double z)
	{
		q.w = w;
		q.x = x;
		q.y = y;
		q.z = z;
	}

	explicit constexpr Quaternion(const Vector3& vector)
	{
		q.w = 1.0;
		q.x = vector.x;
		q.y = vector.y;
		q.z = vector.z;
	}

	explicit constexpr Quaternion(const Vector4& vector)
	{
		q.w = vector.w;
		q.x = vector.x;
		q.y = vector.y;
		q.z = vector.z;
	}

	static constexpr Quaternion Identity()
	{
		return {1.0, 0.0, 0.0, 0.0};
	}

	[[nodiscard]] constexpr double LengthSquared() const
	{
		return q.LengthSquared();
	}

	[[nodiscard]] constexpr double Length() const
	{
		return q.Length();
	}

	[[nodiscard]] constexpr Quaternion Normalized() const
	{
		return Quaternion(q.Normalized());
	}

	[[nodiscard]] constexpr Vector3 Rotate(const Vector3& vector) const
	{
		return {
			q.x * vector.x,
			q.y * vector.y,
			q.z * vector.z
		};
	}


	//============
	// Operators
	//============

	constexpr Quaternion operator*(const Quaternion& other) const
	{
		return Quaternion(q * other.q);
	}

	constexpr Vector3 operator*(const Vector3& vector) const
	{
		const Vector3 qVector = {q.x, q.y, q.z};

		const Vector3 uv = qVector.Cross(vector);

		const Vector3 uuv = qVector.Cross(uv);

		return vector + ((uv * q.w) + uuv) * 2.0;
	}

	constexpr Vector4 operator*(const Vector4& vector) const
	{
		return q * vector;
	}

	constexpr bool operator==(const Quaternion& right) const
	{
		return q == right.q;
	}

	constexpr bool operator==(const Vector4& right) const
	{
		return q == right;
	}

	constexpr bool operator!=(const Quaternion& right) const
	{
		return !(*this == right);
	}

	constexpr bool operator!=(const Vector4& right) const
	{
		return !(*this == right);
	}
};