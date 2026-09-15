//===================================================
// Vector4F.h
// Author: Moca 9/10/2026
// Defines a 4D vector type with float precision.
//===================================================
#pragma once

#include "MathFunc.h"

//! 4D (4-element) vector (wxyz) type with float precision. -Moca
struct Vector4F
{
	float w = 1.0f;
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;


	//===============
	// Constructors
	//===============

	//! Constructs a default Vector4F, equal to Zero().
	constexpr Vector4F() = default;
	//! Constructs a Vector4F of a given w, x, y, and z float value.
	constexpr Vector4F(const float w, const float x, const float y, const float z) : w(w), x(x), y(y), z(z) {};


	//=================
	// Static Presets
	//=================

	//! Returns a Vector4F equal to {1.0, 0.0, 0.0, 0.0}.
	static constexpr Vector4F Zero()
	{
		return {1.0f, 0.0f, 0.0f, 0.0f};
	}

	//! Returns a Vector4F equal to {1.0, 1.0, 1.0, 1.0}.
	static constexpr Vector4F One()
	{
		return {1.0f, 1.0f, 1.0f, 1.0f};
	}


	//===============
	// Math Helpers
	//===============

	// Note: This set of functions is inspired by what Godot has available,
	// but no code has been pulled from Godot's source. -Moca

	//! Returns the absolute value (positive value) of this Vector4F.
	[[nodiscard]] constexpr Vector4F Abs() const
	{
		return {
			Math::AbsF(w),
			Math::AbsF(x),
			Math::AbsF(y),
			Math::AbsF(z)
		};
	}

	//! Returns the rounded up value of this Vector4F.
	[[nodiscard]] constexpr Vector4F Ceil() const
	{
		return {Math::CeilF(w), Math::CeilF(x), Math::CeilF(y), Math::CeilF(z)};
	}

	//! Returns the clamped value of this Vector4F between a given minimum Vector4F and maximum Vector4F value.
	[[nodiscard]] constexpr Vector4F Clamp(const Vector4F& min, const Vector4F& max) const
	{
		return {
			Math::ClampF(w, min.w, max.w),
			Math::ClampF(x, min.x, max.x),
			Math::ClampF(y, min.y, max.y),
			Math::ClampF(z, min.z, max.z)
		};
	}

	//!  Returns the clamped value of this Vector4F between a given minimum float and maximum float value.
	[[nodiscard]] constexpr Vector4F Clamp(const float min, const float max) const
	{
		return {
			Math::ClampF(w, min, max),
			Math::ClampF(x, min, max),
			Math::ClampF(y, min, max),
			Math::ClampF(z, min, max)
		};
	}

	//! Returns the interpolated Vector4F using the given weight.
	[[nodiscard]] constexpr Vector4F CubicInterpolate(
		const Vector4F& b, const Vector4F& preA,
		const Vector4F& preB, const float weight) const
	{
		const float weightSquared	= weight * weight;
		const float weightCubed	= weightSquared * weight;

		return  (*this * 2.0f + (b - preA) * weight +
				(preA * 2.0f - *this * 5.0f + b * 4.0f - preB) * weightSquared +
				(-preA + *this * 3.0f - b * 3.0f + preB) * weightCubed) * 0.5f;
	}

	//! Returns the normalized Vector4F pointed from this Vector4F to another given Vector4F.
	[[nodiscard]] constexpr Vector4F DirectionTo(const Vector4F& other) const
	{
		return (other - *this).Normalized();
	}

	//! Returns the squared distance between this Vector4F and another given Vector4F.
	[[nodiscard]] constexpr float DistanceSquaredTo(const Vector4F& other) const
	{
		return (other - *this).LengthSquared();
	}

	//! Returns the dot product of this Vector4F and another given Vector4F.
	[[nodiscard]] constexpr float Dot(const Vector4F& other) const
	{
		return  w * other.w +
				x * other.x +
				y * other.y +
				z * other.z;
	}

	//! Returns the rounded down value of this Vector4F.
	[[nodiscard]] constexpr Vector4F Floor() const
	{
		return {
			Math::FloorF(w),
			Math::FloorF(x),
			Math::FloorF(y),
			Math::FloorF(z)
		};
	}

	//! Returns whether or not this Vector4F is finite.
	[[nodiscard]] constexpr bool IsFinite() const
	{
		return	Math::IsFiniteF(w) &&
				Math::IsFiniteF(x) &&
				Math::IsFiniteF(y) &&
				Math::IsFiniteF(z);
	}

	//! Returns whether or not this Vector4F is normalized.
	[[nodiscard]] constexpr bool IsNormalized(const float epsilon = 0.00001f) const
	{
		return Math::IsEqualApproxF(LengthSquared(), 1.0f, epsilon);
	}

	//! Returns the squared length of this Vector4F.
	[[nodiscard]] constexpr float LengthSquared() const
	{
		return	w * w +
				x * x +
				y * y +
				z * z;
	}

	//! Returns the length of this Vector4F.
	[[nodiscard]] constexpr float Length() const
	{
		return Math::SqrtF(LengthSquared());
	}

	//! Returns the point between this Vector4F and a given target Vector4F based on a given weight.
	[[nodiscard]] constexpr Vector4F Lerp(const Vector4F& target, const float weight) const
	{
		return {
			Math::LerpF(w, target.w, weight),
			Math::LerpF(x,  target.x, weight),
			Math::LerpF(y,  target.y, weight),
			Math::LerpF(z,  target.z, weight)
		};
	}

	//! Returns the value of this Vector4F with its length limited to a given max length.
	[[nodiscard]] constexpr Vector4F LimitLength(const float maxLength = 1.0f) const
	{
		const float lengthSquared = LengthSquared();
		const float maxLengthSquared = maxLength * maxLength;

		if (lengthSquared <= maxLengthSquared)
		{
			return *this;
		}

		const float scale = maxLength / Math::SqrtF(lengthSquared);

		return *this * scale;
	}

	//! Returns a Vector4F value where each component is the larger value between this Vector4F and another given Vector4F.
	[[nodiscard]] constexpr Vector4F Max(const Vector4F& other) const
	{
		return {
			Math::MaxF(w, other.w),
			Math::MaxF(x, other.x),
			Math::MaxF(y, other.y),
			Math::MaxF(z, other.z)
		};
	}

	//! Returns a Vector4F value where each component is the larger value between this Vector4F and a given float value.
	[[nodiscard]] constexpr Vector4F Max(const float value) const
	{
		return {
			Math::MaxF(w, value),
			Math::MaxF(x, value),
			Math::MaxF(y, value),
			Math::MaxF(z, value)
		};
	}

	//! Returns a Vector4F value where each component is the smaller value between this Vector4F and another given Vector4F.
	[[nodiscard]] constexpr Vector4F Min(const Vector4F& other) const
	{
		return {
			Math::MinF(w, other.w),
			Math::MinF(x, other.x),
			Math::MinF(y, other.y),
			Math::MinF(z, other.z)
		};
	}

	//! Returns a Vector4F value where each component is the smaller value between this Vector4F and a given float value.
	[[nodiscard]] constexpr Vector4F Min(const float value) const
	{
		return {
			Math::MinF(w, value),
			Math::MinF(x, value),
			Math::MinF(y, value),
			Math::MinF(z, value)
		};
	}

	//! Returns the point reached after moving this Vector4F toward another given Vector4F by up to a given delta distance.
	[[nodiscard]] constexpr Vector4F MoveToward(const Vector4F& other, const float delta) const
	{
		const Vector4F difference = other - *this;
		const float distance = difference.Length();

		if (distance <= delta || distance == 0.0f)
		{
			return other;
		}

		return *this + difference / distance * delta;
	}

	//! Returns the unit-length Vector4F in the same direction as this Vector4F.
	[[nodiscard]] constexpr Vector4F Normalized() const
	{
		const float length = Length();

		if (length <= 0.0)
		{
			return Zero();
		}

		return *this / length;
	}

	//! Returns a Vector4F with each component in the range [0, mod] for its corresponding component of a given Vector4F mod value.
	[[nodiscard]] constexpr Vector4F PosMod(const Vector4F& mod) const
	{
		return {
			Math::PosModF(w, mod.w),
			Math::PosModF(x, mod.x),
			Math::PosModF(y, mod.y),
			Math::PosModF(z, mod.z)
		};
	}

	//! Returns a Vector4F with each component in the range [0, mod] for a given float mod value.
	[[nodiscard]] constexpr Vector4F PosMod(const float mod) const
	{
		return {
			Math::PosModF(w, mod),
			Math::PosModF(x, mod),
			Math::PosModF(y, mod),
			Math::PosModF(z, mod)
		};
	}

	//! Returns the Vector4F result of rounding this Vector4F's components to the nearest whole number (integer).
	[[nodiscard]] constexpr Vector4F Round() const
	{
		return {
			Math::RoundF(w),
			Math::RoundF(x),
			Math::RoundF(y),
			Math::RoundF(z)
		};
	}

	//! Returns -1 if a component is negative, 0 if zero, and +1 if positive for each component of this Vector4F.
	[[nodiscard]] constexpr Vector4F Sign() const
	{
		return {
			Math::SignF(w),
			Math::SignF(x),
			Math::SignF(y),
			Math::SignF(z)
		};
	}

	//! Returns the Vector4F result of snapping this Vector4F's components to the nearest corresponding step value.
	[[nodiscard]] constexpr Vector4F Snapped(const Vector4F& step) const
	{
		return {
			Math::SnappedF(w, step.w),
			Math::SnappedF(x, step.x),
			Math::SnappedF(y, step.y),
			Math::SnappedF(z, step.z)
		};
	}

	//! Returns the Vector4F result of snapping this Vector4F's components to the nearest step value.
	[[nodiscard]] constexpr Vector4F Snapped(const float step) const
	{
		return {
			Math::SnappedF(w, step),
			Math::SnappedF(x, step),
			Math::SnappedF(y, step),
			Math::SnappedF(z, step)
		};
	}

	// Comparison
	//! Returns whether or not this Vector4F approximately equals a given Vector4F based on a given epsilon value.
	[[nodiscard]] constexpr bool IsEqualApprox(const Vector4F& other, const float epsilon = 0.00001) const
	{
		return	Math::IsEqualApproxF(w, other.w, epsilon) &&
				Math::IsEqualApproxF(x, other.x, epsilon) &&
				Math::IsEqualApproxF(y, other.y, epsilon) &&
				Math::IsEqualApproxF(z, other.z, epsilon);
	}

	//! Returns whether or not this Vector4F approximately equals zero based on a given epsilon value.
	[[nodiscard]] constexpr bool IsZeroApprox(const float epsilon = 0.00001) const
	{
		return	Math::IsZeroApproxF(w, epsilon) &&
				Math::IsZeroApproxF(x, epsilon) &&
				Math::IsZeroApproxF(y, epsilon) &&
				Math::IsZeroApproxF(z, epsilon);
	}


	//============
	// Operators
	//============

	// Addition
	//! Adds each component of this Vector4F by each component of another given Vector4F.
	constexpr Vector4F operator+(const Vector4F& other) const
	{
		return {
			w + other.w,
			x + other.x,
			y + other.y,
			z + other.z
		};
	}

	//! Adds each component of this Vector4F by each component of another given Vector4F.
	constexpr Vector4F& operator+=(const Vector4F& other)
	{
		w += other.w;
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	// Subtraction
	//! Subtracts each component of this Vector4F by each component of another given Vector4F.
	constexpr Vector4F operator-(const Vector4F& other) const
	{
		return {
			w - other.w,
			x - other.x,
			y - other.y,
			z - other.z
		};
	}

	//! Subtracts each component of this Vector4F by each component of another given Vector4F.
	constexpr Vector4F& operator-=(const Vector4F& other)
	{
		w -= other.w;
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	// Multiplication
	//! Multiplies each component of this Vector4F by each component of another given Vector4F.
	constexpr Vector4F operator*(const Vector4F& other) const
	{
		return {
			w * other.w,
			x * other.x,
			y * other.y,
			z * other.z
		};
	}

	//! Multiplies each component of this Vector4F by each component of another given Vector4F.
	constexpr Vector4F& operator*=(const Vector4F& other)
	{
		w *= other.w;
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	//! Multiplies each component of this Vector4F by a given scalar value.
	constexpr Vector4F operator*(const float scalar) const
	{
		return {
			w * scalar,
			x * scalar,
			y * scalar,
			z * scalar
		};
	}

	//! Multiplies each component of this Vector4F by a given scalar value.
	constexpr Vector4F& operator*=(const float scalar)
	{
		w *= scalar;
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return *this;
	}

	// Division
	//! Divides each component of this Vector4F by each component of another given Vector4F.
	constexpr Vector4F operator/(const Vector4F& other) const
	{
		return {
			w / other.w,
			x / other.x,
			y / other.y,
			z / other.z
		};
	}

	//! Divides each component of this Vector4F by each component of another given Vector4F.
	constexpr Vector4F& operator/=(const Vector4F& other)
	{
		w /= other.w;
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	//! Divides each component of this Vector4F by a given scalar value.
	constexpr Vector4F operator/(const float scalar) const
	{
		return {
			w / scalar,
			x / scalar,
			y / scalar,
			z / scalar
		};
	}

	//! Divides each component of this Vector4F by a given scalar value.
	constexpr Vector4F& operator/=(const float scalar)
	{
		w /= scalar;
		x /= scalar;
		y /= scalar;
		z /= scalar;

		return *this;
	}

	// Unary
	//! Returns the current value of this Vector4F.
	constexpr Vector4F operator+() const
	{
		return *this;
	}

	//! Returns the negative value of this Vector4F.
	constexpr Vector4F operator-() const
	{
		return {-w, -x, -y, -z};
	}

	// Comparison
	//! Returns whether or not this Vector4F is less than a given right Vector4F in order of w, x, y, z.
	constexpr bool operator<(const Vector4F& right) const
	{
		if (w != right.w)
		{
			return w < right.w;
		}

		if (x != right.x)
		{
			return x < right.x;
		}

		if (y != right.y)
		{
			return y < right.y;
		}

		return z < right.z;
	}

	//! Returns whether or not this Vector4F is less than or equal to a given right Vector4F in order of w, x, y, z.
	constexpr bool operator<=(const Vector4F& right) const
	{
		if (w != right.w)
		{
			return w <= right.w;
		}

		if (x != right.x)
		{
			return x <= right.x;
		}

		if (y != right.y)
		{
			return y <= right.y;
		}

		return z <= right.z;
	}

	//! Returns whether or not this Vector4F is greater than a given right Vector4F in order of w, x, y, z.
	constexpr bool operator>(const Vector4F& right) const
	{
		if (w != right.w)
		{
			return w > right.w;
		}

		if (x != right.x)
		{
			return x > right.x;
		}

		if (y != right.y)
		{
			return y > right.y;
		}

		return z > right.z;
	}

	//! Returns whether or not this Vector4F is greater than or equal to a given right Vector4F in order of w, x, y, z.
	constexpr bool operator>=(const Vector4F& right) const
	{
		if (w != right.w)
		{
			return w >= right.w;
		}

		if (x != right.x)
		{
			return x >= right.x;
		}

		if (y != right.y)
		{
			return y >= right.y;
		}

		return z >= right.z;
	}

	//! Returns whether or not this Vector4F is equal to a given right Vector4F.
	constexpr bool operator==(const Vector4F& right) const
	{
		return w == right.w && x == right.x && y == right.y && z == right.z;
	}

	//! Returns whether or not this Vector4F is not equal to a given right Vector4F.
	constexpr bool operator!=(const Vector4F& right) const
	{
		return !(*this == right);
	}
};