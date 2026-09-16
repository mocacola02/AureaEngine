#pragma once

#include "Vector3F.h"
#include "Vector4F.h"

//! Quaternion type with float precision. Used primarily for rendering. Transform3D uses the double precision Quaternion.
struct QuaternionF
{
	Vector4F q;

	constexpr QuaternionF() = default;

	constexpr QuaternionF(const float w, const float x, const float y, const float z)
	{
		q.w = w;
		q.x = x;
		q.y = y;
		q.z = z;
	}

	explicit constexpr QuaternionF(const Vector3F& vector)
	{
		q.w = 1.0f;
		q.x = vector.x;
		q.y = vector.y;
		q.z = vector.z;
	}

	explicit constexpr QuaternionF(const Vector4F& vector)
	{
		q.w = vector.w;
		q.x = vector.x;
		q.y = vector.y;
		q.z = vector.z;
	}

	static constexpr QuaternionF Identity()
	{
		return {1.0f, 0.0f, 0.0f, 0.0f};
	}
	
	[[nodiscard]] constexpr QuaternionF Inverse() const
	{
		return {-q.w, -q.x, -q.y, -q.z};
	}

	[[nodiscard]] constexpr float LengthSquared() const
	{
		return q.LengthSquared();
	}

	[[nodiscard]] constexpr float Length() const
	{
		return q.Length();
	}

	[[nodiscard]] constexpr QuaternionF Normalized() const
	{
		return QuaternionF(q.Normalized());
	}

	[[nodiscard]] constexpr Vector3F Rotate(const Vector3F& vector) const
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

	constexpr QuaternionF operator*(const QuaternionF& other) const
	{
		return QuaternionF(q * other.q);
	}

	constexpr Vector3F operator*(const Vector3F& vector) const
	{
		const Vector3F qVector = {q.x, q.y, q.z};

		const Vector3F uv = qVector.Cross(vector);

		const Vector3F uuv = qVector.Cross(uv);

		return vector + ((uv * q.w) + uuv) * 2.0f;
	}

	constexpr Vector4F operator*(const Vector4F& vector) const
	{
		return q * vector;
	}

	constexpr bool operator==(const QuaternionF& right) const
	{
		return q == right.q;
	}

	constexpr bool operator==(const Vector4F& right) const
	{
		return q == right;
	}

	constexpr bool operator!=(const QuaternionF& right) const
	{
		return !(*this == right);
	}

	constexpr bool operator!=(const Vector4F& right) const
	{
		return !(*this == right);
	}
};