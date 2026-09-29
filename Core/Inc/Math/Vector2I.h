//===================================================
// Vector2I.h
// Author: Moca 9/29/2026
// Defines a 2D vector type with int32 precision.
//===================================================
#pragma once

#include "Int.h"
#include "MathFunc.h"
#include "Vector2.h"
#include "Vector2F.h"

// TODO: Double check if comments are accurate

//! 2D (2-element) vector (xy) type with int32 precision. -Moca
struct Vector2I
{
	int32 x = 0;
	int32 y = 0;

	//===============
	// Constructors
	//===============

	//! Constructs a default Vector2I, equal to Zero().
	constexpr Vector2I() = default;
	//! Constructs a Vector2I of a given x and y int32 value.
	constexpr Vector2I(const int32 x, const int32 y) : x(x), y(y) {}

	//=================
	// Static Presets
	//=================

	//! Returns a Vector2I equal to {0, 0}.
	static constexpr Vector2I Zero()
	{
		return {0, 0};
	}

	//! Returns a Vector2I equal to {1, 1}.
	static constexpr Vector2I One()
	{
		return {1, 1};
	}

	//! Returns a Vector2I equal to {1, 0}.
	static constexpr Vector2I Right()
	{
		return {1, 0};
	}

	//! Returns a Vector2I equal to {0, 1}.
	static constexpr Vector2I Up()
	{
		return {0, 1};
	}


	//===============
	// Math Helpers
	//===============

	// Note: This set of functions is inspired by what Godot has available,
	// but no code has been pulled from Godot's source. -Moca

	//! Returns the absolute value (positive value) of this Vector2I.
	[[nodiscard]] constexpr Vector2I Abs() const
	{
		return {
			Math::AbsI(x),
			Math::AbsI(y)
		};
	}

	//! Returns the clamped value of this Vector2I between a given minimum Vector2I and maximum Vector2I value.
	[[nodiscard]] constexpr Vector2I Clamp(const Vector2I& min, const Vector2I& max) const
	{
		return {
			Math::ClampI(x, min.x, max.x),
			Math::ClampI(y, min.y, max.y)
		};
	}

	//!  Returns the clamped value of this Vector2I between a given minimum int32 and maximum int32 value.
	[[nodiscard]] constexpr Vector2I Clamp(const int32 min, const int32 max) const
	{
		return {
			Math::ClampI(x, min, max),
			Math::ClampI(y, min, max)
		};
	}

	//! Returns the dot product of this Vector2I and another given Vector2I.
	[[nodiscard]] constexpr int32 Dot(const Vector2I& other) const
	{
		return	x * other.x + y * other.y;
	}

	//! Returns whether or not this Vector2I is finite.
	[[nodiscard]] constexpr bool IsFinite() const
	{
		return Math::IsFiniteI(x) && Math::IsFiniteI(y);
	}

	//! Returns the squared length of this Vector2I.
	[[nodiscard]] constexpr int32 LengthSquared() const
	{
		return	x * x + y * y;
	}

	//! Returns the length of this Vector2I.
	[[nodiscard]] constexpr float Length() const
	{
		return Math::SqrtF(LengthSquared());
	}

	//! Returns a Vector2I value where each component is the larger value between this Vector2I and another given Vector2I.
	[[nodiscard]] constexpr Vector2I Max(const Vector2I& other) const
	{
		return {
			Math::MaxI(x, other.x),
			Math::MaxI(y, other.y)
		};
	}

	//! Returns a Vector2I value where each component is the larger value between this Vector2I and a given int32 value.
	[[nodiscard]] constexpr Vector2I Max(const int32 value) const
	{
		return {
			Math::MaxI(x, value),
			Math::MaxI(y, value)
		};
	}

	//! Returns a Vector2I value where each component is the smaller value between this Vector2I and another given Vector2I.
	[[nodiscard]] constexpr Vector2I Min(const Vector2I& other) const
	{
		return {
			Math::MinI(x, other.x),
			Math::MinI(y, other.y)
		};
	}

	//! Returns a Vector2I value where each component is the smaller value between this Vector2I and a given int32 value.
	[[nodiscard]] constexpr Vector2I Min(const int32 value) const
	{
		return {
			Math::MinI(x, value),
			Math::MinI(y, value)
		};
	}

	//! Returns -1 if a component is negative, 0 if zero, and +1 if positive for each component of this Vector2I.
	[[nodiscard]] constexpr Vector2I Sign() const
	{
		return {
			Math::SignI(x),
			Math::SignI(y)
		};
	}


	//============
	// Operators
	//============

	// Addition
	//! Adds each component of this Vector2I by each component of another given Vector2I.
	constexpr Vector2I operator+(const Vector2I& other) const
	{
		return {
			x + other.x,
			y + other.y
		};
	}

	//! Adds each component of this Vector2I by each component of another given Vector2I.
	constexpr Vector2I& operator+=(const Vector2I& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	// Subtraction
	//! Subtracts each component of this Vector2I by each component of another given Vector2I.
	constexpr Vector2I operator-(const Vector2I& other) const
	{
		return {
			x - other.x,
			y - other.y
		};
	}

	//! Subtracts each component of this Vector2I by each component of another given Vector2I.
	constexpr Vector2I& operator-=(const Vector2I& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	// Multiplication
	//! Multiplies each component of this Vector2I by each component of another given Vector2I.
	constexpr Vector2I operator*(const Vector2I& other) const
	{
		return {
			x * other.x,
			y * other.y
		};
	}

	//! Multiplies each component of this Vector2I by each component of another given Vector2I.
	constexpr Vector2I& operator*=(const Vector2I& other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	//! Multiplies each component of this Vector2I by a given scalar value.
	constexpr Vector2I operator*(const int32 scalar) const
	{
		return {
			x * scalar,
			y * scalar
		};
	}

	//! Multiplies each component of this Vector2I by a given scalar value.
	constexpr Vector2I& operator*=(const int32 scalar)
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}

	// Division
	//! Divides each component of this Vector2I by each component of another given Vector2I.
	constexpr Vector2I operator/(const Vector2I& other) const
	{
		return {
			x / other.x,
			y / other.y
		};
	}

	//! Divides each component of this Vector2I by each component of another given Vector2I.
	constexpr Vector2I& operator/=(const Vector2I& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	//! Divides each component of this Vector2I by each component of a given Vector2F.
	constexpr Vector2I operator/(const Vector2F& other) const
	{
		return {
			static_cast<int32>(x / other.x),
			static_cast<int32>(y / other.y)
		};
	}

	//! Divides each component of this Vector2I by each component of a given Vector2F.
	constexpr Vector2I& operator/=(const Vector2F& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	//! Divides each component of this Vector2I by each component of a given Vector2.
	constexpr Vector2I operator/(const Vector2& other) const
	{
		return {
			static_cast<int32>(x / other.x),
			static_cast<int32>(y / other.y)
		};
	}

	//! Divides each component of this Vector2I by each component of a given Vector2.
	constexpr Vector2I& operator/=(const Vector2& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	//! Divides each component of this Vector2I by a given scalar value.
	constexpr Vector2I operator/(const int32 scalar) const
	{
		return {
			x / scalar,
			y / scalar
		};
	}

	//! Divides each component of this Vector2I by a given scalar value.
	constexpr Vector2I& operator/=(const int32 scalar)
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}

	//! Divides each component of this Vector2I by a given float scalar value.
	constexpr Vector2I operator/(const float scalar) const
	{
		return {
			static_cast<int32>(x / scalar),
			static_cast<int32>(y / scalar)
		};
	}

	//! Divides each component of this Vector2I by a given float scalar value.
	constexpr Vector2I& operator/=(const float scalar)
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}

	//! Divides each component of this Vector2I by a given double scalar value.
	constexpr Vector2I operator/(const double scalar) const
	{
		return {
			static_cast<int32>(x / scalar),
			static_cast<int32>(y / scalar)
		};
	}

	//! Divides each component of this Vector2I by a given double scalar value.
	constexpr Vector2I& operator/=(const double scalar)
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}

	// Unary
	//! Returns the current value of this Vector2I.
	constexpr Vector2I operator+() const
	{
		return *this;
	}

	//! Returns the negative value of this Vector2I.
	constexpr Vector2I operator-() const
	{
		return {-x, -y};
	}

	// Increment
	constexpr Vector2I operator++() const
	{
		return {x + 1, y + 1};
	}

	constexpr Vector2I operator--() const
	{
		return {x - 1, y - 1};
	}

	// Comparison
	//! Returns whether or not this Vector2I is less than a given right Vector2I in order of x, y, z.
	constexpr bool operator<(const Vector2I& right) const
	{
		if (x != right.x)
		{
			return x < right.x;
		}

		return y < right.y;
	}

	//! Returns whether or not this Vector2I is less than a given right Vector2 in order of x, y, z.
	constexpr bool operator<(const Vector2& right) const
	{
		if (x != right.x)
		{
			return x < right.x;
		}

		return y < right.y;
	}

	//! Returns whether or not this Vector2I is less than a given right Vector2F in order of x, y, z.
	constexpr bool operator<(const Vector2F& right) const
	{
		if (x != right.x)
		{
			return x < right.x;
		}

		return y < right.y;
	}

	//! Returns whether or not this Vector2I is less than or equal to a given right Vector2I in order of x, y, z.
	constexpr bool operator<=(const Vector2I& right) const
	{
		if (x != right.x)
		{
			return x <= right.x;
		}

		return y <= right.y;
	}

	//! Returns whether or not this Vector2I is less than or equal to a given right Vector2I in order of x, y, z.
	constexpr bool operator<=(const Vector2& right) const
	{
		if (x != right.x)
		{
			return x <= right.x;
		}

		return y <= right.y;
	}

	//! Returns whether or not this Vector2I is less than or equal to a given right Vector2I in order of x, y, z.
	constexpr bool operator<=(const Vector2F& right) const
	{
		if (x != right.x)
		{
			return x <= right.x;
		}

		return y <= right.y;
	}

	//! Returns whether or not this Vector2I is greater than a given right Vector2I in order of x, y, z.
	constexpr bool operator>(const Vector2I& right) const
	{
		if (x != right.x)
		{
			return x > right.x;
		}

		return y > right.y;
	}

	//! Returns whether or not this Vector2I is greater than a given right Vector2I in order of x, y, z.
	constexpr bool operator>(const Vector2& right) const
	{
		if (x != right.x)
		{
			return x > right.x;
		}

		return y > right.y;
	}

	//! Returns whether or not this Vector2I is greater than a given right Vector2I in order of x, y, z.
	constexpr bool operator>(const Vector2F& right) const
	{
		if (x != right.x)
		{
			return x > right.x;
		}

		return y > right.y;
	}

	//! Returns whether or not this Vector2I is greater than or equal to a given right Vector2I in order of x, y, z.
	constexpr bool operator>=(const Vector2I& right) const
	{
		if (x != right.x)
		{
			return x >= right.x;
		}

		return y >= right.y;
	}

	//! Returns whether or not this Vector2I is greater than or equal to a given right Vector2I in order of x, y, z.
	constexpr bool operator>=(const Vector2& right) const
	{
		if (x != right.x)
		{
			return x >= right.x;
		}

		return y >= right.y;
	}

	//! Returns whether or not this Vector2I is greater than or equal to a given right Vector2I in order of x, y, z.
	constexpr bool operator>=(const Vector2F& right) const
	{
		if (x != right.x)
		{
			return x >= right.x;
		}

		return y >= right.y;
	}

	//! Returns whether or not this Vector2I is equal to a given right Vector2I.
	constexpr bool operator==(const Vector2I& right) const
	{
		return x == right.x && y == right.y;
	}

	//! Returns whether or not this Vector2I is equal to a given right Vector2I.
	constexpr bool operator==(const Vector2& right) const
	{
		return x == right.x && y == right.y;
	}

	//! Returns whether or not this Vector2I is equal to a given right Vector2I.
	constexpr bool operator==(const Vector2F& right) const
	{
		return x == right.x && y == right.y;
	}

	//! Returns whether or not this Vector2I is not equal to a given right Vector2I.
	constexpr bool operator!=(const Vector2I& right) const
	{
		return !(*this == right);
	}

	//! Returns whether or not this Vector2I is not equal to a given right Vector2I.
	constexpr bool operator!=(const Vector2& right) const
	{
		return !(*this == right);
	}

	//! Returns whether or not this Vector2I is not equal to a given right Vector2I.
	constexpr bool operator!=(const Vector2F& right) const
	{
		return !(*this == right);
	}
};