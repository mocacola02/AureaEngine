//===================================================
// Vector4.h
// Author: Moca 9/10/2026
// Defines a 4D vector type with double precision.
//===================================================
#pragma once

#include "MathFunc.h"

//! 4D (4-element) vector (wxyz) type with double precision. The float variant, Vector4F, is primarily used in rendering. -Moca
struct Vector4
{
	double w = 1.0;
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;


	//===============
	// Constructors
	//===============

	//! Constructs a default Vector4, equal to Zero().
	constexpr Vector4() = default;
	//! Constructs a Vector4 of a given w, x, y, and z double value.
	constexpr Vector4(const double w, const double x, const double y, const double z) : w(w), x(x), y(y), z(z) {};


	//=================
	// Static Presets
	//=================

	//! Returns a Vector4 equal to {1.0, 0.0, 0.0, 0.0}.
	static constexpr Vector4 Zero()
	{
		return {1.0, 0.0, 0.0, 0.0};
	}

	//! Returns a Vector4 equal to {1.0, 1.0, 1.0, 1.0}.
	static constexpr Vector4 One()
	{
		return {1.0, 1.0, 1.0, 1.0};
	}


	//===============
	// Math Helpers
	//===============

	// Note: This set of functions is inspired by what Godot has available,
	// but no code has been pulled from Godot's source. -Moca

	//! Returns the absolute value (positive value) of this Vector4.
	[[nodiscard]] constexpr Vector4 Abs() const
	{
		return {
			Math::Abs(w),
			Math::Abs(x),
			Math::Abs(y),
			Math::Abs(z)
		};
	}

	//! Returns the rounded up value of this Vector4.
	[[nodiscard]] constexpr Vector4 Ceil() const
	{
		return {Math::Ceil(w), Math::Ceil(x), Math::Ceil(y), Math::Ceil(z)};
	}

	//! Returns the clamped value of this Vector4 between a given minimum Vector4 and maximum Vector4 value.
	[[nodiscard]] constexpr Vector4 Clamp(const Vector4& min, const Vector4& max) const
	{
		return {
			Math::Clamp(w, min.w, max.w),
			Math::Clamp(x, min.x, max.x),
			Math::Clamp(y, min.y, max.y),
			Math::Clamp(z, min.z, max.z)
		};
	}

	//!  Returns the clamped value of this Vector4 between a given minimum double and maximum double value.
	[[nodiscard]] constexpr Vector4 Clamp(const double min, const double max) const
	{
		return {
			Math::Clamp(w, min, max),
			Math::Clamp(x, min, max),
			Math::Clamp(y, min, max),
			Math::Clamp(z, min, max)
		};
	}

	//! Returns the interpolated Vector4 using the given weight.
	[[nodiscard]] constexpr Vector4 CubicInterpolate(
		const Vector4& b, const Vector4& preA,
		const Vector4& preB, const double weight) const
	{
		const double weightSquared	= weight * weight;
		const double weightCubed	= weightSquared * weight;

		return  (*this * 2.0 + (b - preA) * weight +
				(preA * 2.0 - *this * 5.0 + b * 4.0 - preB) * weightSquared +
				(-preA + *this * 3.0 - b * 3.0 + preB) * weightCubed) * 0.5;
	}

	//! Returns the normalized Vector4 pointed from this Vector4 to another given Vector4.
	[[nodiscard]] constexpr Vector4 DirectionTo(const Vector4& other) const
	{
		return (other - *this).Normalized();
	}

	//! Returns the squared distance between this Vector4 and another given Vector4.
	[[nodiscard]] constexpr double DistanceSquaredTo(const Vector4& other) const
	{
		return (other - *this).LengthSquared();
	}

	//! Returns the dot product of this Vector4 and another given Vector4.
	[[nodiscard]] constexpr double Dot(const Vector4& other) const
	{
		return	w * other.w +
				x * other.x +
				y * other.y +
				z * other.z;
	}

	//! Returns the rounded down value of this Vector4.
	[[nodiscard]] constexpr Vector4 Floor() const
	{
		return {
			Math::Floor(w),
			Math::Floor(x),
			Math::Floor(y),
			Math::Floor(z)
		};
	}

	//! Returns whether or not this Vector4 is finite.
	[[nodiscard]] constexpr bool IsFinite() const
	{
		return	Math::IsFinite(w) &&
				Math::IsFinite(x) &&
				Math::IsFinite(y) &&
				Math::IsFinite(z);
	}

	//! Returns whether or not this Vector4 is normalized.
	[[nodiscard]] constexpr bool IsNormalized(const double epsilon = 0.00001) const
	{
		return Math::IsEqualApprox(LengthSquared(), 1.0, epsilon);
	}

	//! Returns the squared length of this Vector4.
	[[nodiscard]] constexpr double LengthSquared() const
	{
		return	w * w +
				x * x +
				y * y +
				z * z;
	}

	//! Returns the length of this Vector4.
	[[nodiscard]] constexpr double Length() const
	{
		return Math::Sqrt(LengthSquared());
	}

	//! Returns the point between this Vector4 and a given target Vector4 based on a given weight.
	[[nodiscard]] constexpr Vector4 Lerp(const Vector4& target, const double weight) const
	{
		return {
			Math::Lerp(w, target.w, weight),
			Math::Lerp(x,  target.x, weight),
			Math::Lerp(y,  target.y, weight),
			Math::Lerp(z,  target.z, weight)
		};
	}

	//! Returns the value of this Vector4 with its length limited to a given max length.
	[[nodiscard]] constexpr Vector4 LimitLength(const double maxLength = 1.0) const
	{
		const double lengthSquared = LengthSquared();
		const double maxLengthSquared = maxLength * maxLength;

		if (lengthSquared <= maxLengthSquared)
		{
			return *this;
		}

		const double scale = maxLength / Math::Sqrt(lengthSquared);

		return *this * scale;
	}

	//! Returns a Vector4 value where each component is the larger value between this Vector4 and another given Vector4.
	[[nodiscard]] constexpr Vector4 Max(const Vector4& other) const
	{
		return {
			Math::Max(w, other.w),
			Math::Max(x, other.x),
			Math::Max(y, other.y),
			Math::Max(z, other.z)
		};
	}

	//! Returns a Vector4 value where each component is the larger value between this Vector4 and a given double value.
	[[nodiscard]] constexpr Vector4 Max(const double value) const
	{
		return {
			Math::Max(w, value),
			Math::Max(x, value),
			Math::Max(y, value),
			Math::Max(z, value)
		};
	}

	//! Returns a Vector4 value where each component is the smaller value between this Vector4 and another given Vector4.
	[[nodiscard]] constexpr Vector4 Min(const Vector4& other) const
	{
		return {
			Math::Min(w, other.w),
			Math::Min(x, other.x),
			Math::Min(y, other.y),
			Math::Min(z, other.z)
		};
	}

	//! Returns a Vector4 value where each component is the smaller value between this Vector4 and a given double value.
	[[nodiscard]] constexpr Vector4 Min(const double value) const
	{
		return {
			Math::Min(w, value),
			Math::Min(x, value),
			Math::Min(y, value),
			Math::Min(z, value)
		};
	}

	//! Returns the point reached after moving this Vector4 toward another given Vector4 by up to a given delta distance.
	[[nodiscard]] constexpr Vector4 MoveToward(const Vector4& other, const double delta) const
	{
		const Vector4 difference = other - *this;
		const double distance = difference.Length();

		if (distance <= delta || distance == 0.0)
		{
			return other;
		}

		return *this + difference / distance * delta;
	}

	//! Returns the unit-length Vector4 in the same direction as this Vector4.
	[[nodiscard]] constexpr Vector4 Normalized() const
	{
		const double length = Length();

		if (length <= 0.0)
		{
			return Zero();
		}

		return *this / length;
	}

	//! Returns a Vector4 with each component in the range [0, mod] for its corresponding component of a given Vector4 mod value.
	[[nodiscard]] constexpr Vector4 PosMod(const Vector4& mod) const
	{
		return {
			Math::PosMod(w, mod.w),
			Math::PosMod(x, mod.x),
			Math::PosMod(y, mod.y),
			Math::PosMod(z, mod.z)
		};
	}

	//! Returns a Vector4 with each component in the range [0, mod] for a given double mod value.
	[[nodiscard]] constexpr Vector4 PosMod(const double mod) const
	{
		return {
			Math::PosMod(w, mod),
			Math::PosMod(x, mod),
			Math::PosMod(y, mod),
			Math::PosMod(z, mod)
		};
	}

	//! Returns the Vector4 result of rounding this Vector4's components to the nearest whole number (integer).
	[[nodiscard]] constexpr Vector4 Round() const
	{
		return {
			Math::Round(w),
			Math::Round(x),
			Math::Round(y),
			Math::Round(z)
		};
	}

	//! Returns -1 if a component is negative, 0 if zero, and +1 if positive for each component of this Vector4.
	[[nodiscard]] constexpr Vector4 Sign() const
	{
		return {
			Math::Sign(w),
			Math::Sign(x),
			Math::Sign(y),
			Math::Sign(z)
		};
	}

	//! Returns the Vector4 result of snapping this Vector4's components to the nearest corresponding step value.
	[[nodiscard]] constexpr Vector4 Snapped(const Vector4& step) const
	{
		return {
			Math::Snapped(w, step.w),
			Math::Snapped(x, step.x),
			Math::Snapped(y, step.y),
			Math::Snapped(z, step.z)
		};
	}

	//! Returns the Vector4 result of snapping this Vector4's components to the nearest step value.
	[[nodiscard]] constexpr Vector4 Snapped(const double step) const
	{
		return {
			Math::Snapped(w, step),
			Math::Snapped(x, step),
			Math::Snapped(y, step),
			Math::Snapped(z, step)
		};
	}

	// Comparison
	//! Returns whether or not this Vector4 approximately equals a given Vector4 based on a given epsilon value.
	[[nodiscard]] constexpr bool IsEqualApprox(const Vector4& other, const double epsilon = 0.00001) const
	{
		return	Math::IsEqualApprox(w, other.w, epsilon) &&
				Math::IsEqualApprox(x, other.x, epsilon) &&
				Math::IsEqualApprox(y, other.y, epsilon) &&
				Math::IsEqualApprox(z, other.z, epsilon);
	}

	//! Returns whether or not this Vector4 approximately equals zero based on a given epsilon value.
	[[nodiscard]] constexpr bool IsZeroApprox(const double epsilon = 0.00001) const
	{
		return	Math::IsZeroApprox(w, epsilon) &&
				Math::IsZeroApprox(x, epsilon) &&
				Math::IsZeroApprox(y, epsilon) &&
				Math::IsZeroApprox(z, epsilon);
	}


	//============
	// Operators
	//============

	// Addition
	//! Adds each component of this Vector4 by each component of another given Vector4.
	constexpr Vector4 operator+(const Vector4& other) const
	{
		return {
			w + other.w,
			x + other.x,
			y + other.y,
			z + other.z
		};
	}

	//! Adds each component of this Vector4 by each component of another given Vector4.
	constexpr Vector4& operator+=(const Vector4& other)
	{
		w += other.w;
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	// Subtraction
	//! Subtracts each component of this Vector4 by each component of another given Vector4.
	constexpr Vector4 operator-(const Vector4& other) const
	{
		return {
			w - other.w,
			x - other.x,
			y - other.y,
			z - other.z
		};
	}

	//! Subtracts each component of this Vector4 by each component of another given Vector4.
	constexpr Vector4& operator-=(const Vector4& other)
	{
		w -= other.w;
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	// Multiplication
	//! Multiplies each component of this Vector4 by each component of another given Vector4.
	constexpr Vector4 operator*(const Vector4& other) const
	{
		return {
			w * other.w,
			x * other.x,
			y * other.y,
			z * other.z
		};
	}

	//! Multiplies each component of this Vector4 by each component of another given Vector4.
	constexpr Vector4& operator*=(const Vector4& other)
	{
		w *= other.w;
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	//! Multiplies each component of this Vector4 by a given scalar value.
	constexpr Vector4 operator*(const double scalar) const
	{
		return {
			w * scalar,
			x * scalar,
			y * scalar,
			z * scalar
		};
	}

	//! Multiplies each component of this Vector4 by a given scalar value.
	constexpr Vector4& operator*=(const double scalar)
	{
		w *= scalar;
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return *this;
	}

	// Division
	//! Divides each component of this Vector4 by each component of another given Vector4.
	constexpr Vector4 operator/(const Vector4& other) const
	{
		return {
			w / other.w,
			x / other.x,
			y / other.y,
			z / other.z
		};
	}

	//! Divides each component of this Vector4 by each component of another given Vector4.
	constexpr Vector4& operator/=(const Vector4& other)
	{
		w /= other.w;
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	//! Divides each component of this Vector4 by a given scalar value.
	constexpr Vector4 operator/(const double scalar) const
	{
		return {
			w / scalar,
			x / scalar,
			y / scalar,
			z / scalar
		};
	}

	//! Divides each component of this Vector4 by a given scalar value.
	constexpr Vector4& operator/=(const double scalar)
	{
		w /= scalar;
		x /= scalar;
		y /= scalar;
		z /= scalar;

		return *this;
	}

	// Unary
	//! Returns the current value of this Vector4.
	constexpr Vector4 operator+() const
	{
		return *this;
	}

	//! Returns the negative value of this Vector4.
	constexpr Vector4 operator-() const
	{
		return {-w, -x, -y, -z};
	}

	// Comparison
	//! Returns whether or not this Vector4 is less than a given right Vector4 in order of w, x, y, z.
	constexpr bool operator<(const Vector4& right) const
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

	//! Returns whether or not this Vector4 is less than or equal to a given right Vector4 in order of w, x, y, z.
	constexpr bool operator<=(const Vector4& right) const
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

	//! Returns whether or not this Vector4 is greater than a given right Vector4 in order of w, x, y, z.
	constexpr bool operator>(const Vector4& right) const
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

	//! Returns whether or not this Vector4 is greater than or equal to a given right Vector4 in order of w, x, y, z.
	constexpr bool operator>=(const Vector4& right) const
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

	//! Returns whether or not this Vector4 is equal to a given right Vector4.
	constexpr bool operator==(const Vector4& right) const
	{
		return w == right.w && x == right.x && y == right.y && z == right.z;
	}

	//! Returns whether or not this Vector4 is not equal to a given right Vector4.
	constexpr bool operator!=(const Vector4& right) const
	{
		return !(*this == right);
	}
};