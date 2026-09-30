//===================================================
// Vector2U.h
// Author: Moca 9/29/2026
// Defines a 2D vector type with uint32 precision.
//===================================================
#pragma once

#include "Int.h"
#include "MathFunc.h"
#include "Vector2.h"
#include "Vector2F.h"

// TODO: Double check if comments are accurate

//! 2D (2-element) vector (xy) type with uint32 precision. -Moca
struct Vector2U
{
	uint32 x = 0;
	uint32 y = 0;

	//===============
	// Constructors
	//===============

	//! Constructs a default Vector2U, equal to Zero().
	constexpr Vector2U() = default;
	//! Constructs a Vector2U of a given x and y uint32 value.
	constexpr Vector2U(const uint32 x, const uint32 y) : x(x), y(y) {}

	//=================
	// Static Presets
	//=================

	//! Returns a Vector2U equal to {0, 0}.
	static constexpr Vector2U Zero()
	{
		return {0, 0};
	}

	//! Returns a Vector2U equal to {1, 1}.
	static constexpr Vector2U One()
	{
		return {1, 1};
	}

	//! Returns a Vector2U equal to {1, 0}.
	static constexpr Vector2U Right()
	{
		return {1, 0};
	}

	//! Returns a Vector2U equal to {0, 1}.
	static constexpr Vector2U Up()
	{
		return {0, 1};
	}


	//===============
	// Math Helpers
	//===============

	// Note: This set of functions is inspired by what Godot has available,
	// but no code has been pulled from Godot's source. -Moca

	//! Returns the absolute value (positive value) of this Vector2U.
	constexpr Vector2U Abs() const
	{
		return {
			Math::AbsI(x),
			Math::AbsI(y)
		};
	}

	//! Returns the clamped value of this Vector2U between a given minimum Vector2U and maximum Vector2U value.
	constexpr Vector2U Clamp(const Vector2U& min, const Vector2U& max) const
	{
		return {
			Math::ClampI(x, min.x, max.x),
			Math::ClampI(y, min.y, max.y)
		};
	}

	//!  Returns the clamped value of this Vector2U between a given minimum uint32 and maximum uint32 value.
	constexpr Vector2U Clamp(const uint32 min, const uint32 max) const
	{
		return {
			Math::ClampI(x, min, max),
			Math::ClampI(y, min, max)
		};
	}

	//! Returns the dot product of this Vector2U and another given Vector2U.
	constexpr uint32 Dot(const Vector2U& other) const
	{
		return	x * other.x + y * other.y;
	}

	//! Returns whether or not this Vector2U is finite.
	constexpr bool IsFinite() const
	{
		return Math::IsFiniteI(x) && Math::IsFiniteI(y);
	}

	//! Returns the squared length of this Vector2U.
	constexpr uint32 LengthSquared() const
	{
		return	x * x + y * y;
	}

	//! Returns the length of this Vector2U.
	constexpr float Length() const
	{
		return Math::SqrtF(LengthSquared());
	}

	//! Returns a Vector2U value where each component is the larger value between this Vector2U and another given Vector2U.
	constexpr Vector2U Max(const Vector2U& other) const
	{
		return {
			Math::MaxI(x, other.x),
			Math::MaxI(y, other.y)
		};
	}

	//! Returns a Vector2U value where each component is the larger value between this Vector2U and a given uint32 value.
	constexpr Vector2U Max(const uint32 value) const
	{
		return {
			Math::MaxI(x, value),
			Math::MaxI(y, value)
		};
	}

	//! Returns a Vector2U value where each component is the smaller value between this Vector2U and another given Vector2U.
	constexpr Vector2U Min(const Vector2U& other) const
	{
		return {
			Math::MinI(x, other.x),
			Math::MinI(y, other.y)
		};
	}

	//! Returns a Vector2U value where each component is the smaller value between this Vector2U and a given uint32 value.
	constexpr Vector2U Min(const uint32 value) const
	{
		return {
			Math::MinI(x, value),
			Math::MinI(y, value)
		};
	}

	//! Returns -1 if a component is negative, 0 if zero, and +1 if positive for each component of this Vector2U.
	constexpr Vector2U Sign() const
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
	//! Adds each component of this Vector2U by each component of another given Vector2U.
	constexpr Vector2U operator+(const Vector2U& other) const
	{
		return {
			x + other.x,
			y + other.y
		};
	}

	//! Adds each component of this Vector2U by each component of another given Vector2U.
	constexpr Vector2U& operator+=(const Vector2U& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	// Subtraction
	//! Subtracts each component of this Vector2U by each component of another given Vector2U.
	constexpr Vector2U operator-(const Vector2U& other) const
	{
		return {
			x - other.x,
			y - other.y
		};
	}

	//! Subtracts each component of this Vector2U by each component of another given Vector2U.
	constexpr Vector2U& operator-=(const Vector2U& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	// Multiplication
	//! Multiplies each component of this Vector2U by each component of another given Vector2U.
	constexpr Vector2U operator*(const Vector2U& other) const
	{
		return {
			x * other.x,
			y * other.y
		};
	}

	//! Multiplies each component of this Vector2U by each component of another given Vector2U.
	constexpr Vector2U& operator*=(const Vector2U& other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	//! Multiplies each component of this Vector2U by a given scalar value.
	constexpr Vector2U operator*(const uint32 scalar) const
	{
		return {
			x * scalar,
			y * scalar
		};
	}

	//! Multiplies each component of this Vector2U by a given scalar value.
	constexpr Vector2U& operator*=(const uint32 scalar)
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}

	// Division
	//! Divides each component of this Vector2U by each component of another given Vector2U.
	constexpr Vector2U operator/(const Vector2U& other) const
	{
		return {
			x / other.x,
			y / other.y
		};
	}

	//! Divides each component of this Vector2U by each component of another given Vector2U.
	constexpr Vector2U& operator/=(const Vector2U& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	//! Divides each component of this Vector2U by each component of a given Vector2F.
	constexpr Vector2U operator/(const Vector2F& other) const
	{
		return {
			static_cast<uint32>(x / other.x),
			static_cast<uint32>(y / other.y)
		};
	}

	//! Divides each component of this Vector2U by each component of a given Vector2F.
	constexpr Vector2U& operator/=(const Vector2F& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	//! Divides each component of this Vector2U by each component of a given Vector2.
	constexpr Vector2U operator/(const Vector2& other) const
	{
		return {
			static_cast<uint32>(x / other.x),
			static_cast<uint32>(y / other.y)
		};
	}

	//! Divides each component of this Vector2U by each component of a given Vector2.
	constexpr Vector2U& operator/=(const Vector2& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	//! Divides each component of this Vector2U by a given scalar value.
	constexpr Vector2U operator/(const uint32 scalar) const
	{
		return {
			x / scalar,
			y / scalar
		};
	}

	//! Divides each component of this Vector2U by a given scalar value.
	constexpr Vector2U& operator/=(const uint32 scalar)
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}

	//! Divides each component of this Vector2U by a given float scalar value.
	constexpr Vector2U operator/(const float scalar) const
	{
		return {
			static_cast<uint32>(x / scalar),
			static_cast<uint32>(y / scalar)
		};
	}

	//! Divides each component of this Vector2U by a given float scalar value.
	constexpr Vector2U& operator/=(const float scalar)
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}

	//! Divides each component of this Vector2U by a given double scalar value.
	constexpr Vector2U operator/(const double scalar) const
	{
		return {
			static_cast<uint32>(x / scalar),
			static_cast<uint32>(y / scalar)
		};
	}

	//! Divides each component of this Vector2U by a given double scalar value.
	constexpr Vector2U& operator/=(const double scalar)
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}

	// Unary
	//! Returns the current value of this Vector2U.
	constexpr Vector2U operator+() const
	{
		return *this;
	}

	//! Returns the negative value of this Vector2U.
	constexpr Vector2U operator-() const
	{
		return {-x, -y};
	}

	// Increment
	constexpr Vector2U operator++() const
	{
		return {x + 1, y + 1};
	}

	constexpr Vector2U operator--() const
	{
		return {x - 1, y - 1};
	}

	// Comparison
	//! Returns whether or not this Vector2U is less than a given right Vector2U in order of x, y, z.
	constexpr bool operator<(const Vector2U& right) const
	{
		if (x != right.x)
		{
			return x < right.x;
		}

		return y < right.y;
	}

	//! Returns whether or not this Vector2U is less than a given right Vector2 in order of x, y, z.
	constexpr bool operator<(const Vector2& right) const
	{
		if (x != right.x)
		{
			return x < right.x;
		}

		return y < right.y;
	}

	//! Returns whether or not this Vector2U is less than a given right Vector2F in order of x, y, z.
	constexpr bool operator<(const Vector2F& right) const
	{
		if (x != right.x)
		{
			return x < right.x;
		}

		return y < right.y;
	}

	//! Returns whether or not this Vector2U is less than or equal to a given right Vector2U in order of x, y, z.
	constexpr bool operator<=(const Vector2U& right) const
	{
		if (x != right.x)
		{
			return x <= right.x;
		}

		return y <= right.y;
	}

	//! Returns whether or not this Vector2U is less than or equal to a given right Vector2U in order of x, y, z.
	constexpr bool operator<=(const Vector2& right) const
	{
		if (x != right.x)
		{
			return x <= right.x;
		}

		return y <= right.y;
	}

	//! Returns whether or not this Vector2U is less than or equal to a given right Vector2U in order of x, y, z.
	constexpr bool operator<=(const Vector2F& right) const
	{
		if (x != right.x)
		{
			return x <= right.x;
		}

		return y <= right.y;
	}

	//! Returns whether or not this Vector2U is greater than a given right Vector2U in order of x, y, z.
	constexpr bool operator>(const Vector2U& right) const
	{
		if (x != right.x)
		{
			return x > right.x;
		}

		return y > right.y;
	}

	//! Returns whether or not this Vector2U is greater than a given right Vector2U in order of x, y, z.
	constexpr bool operator>(const Vector2& right) const
	{
		if (x != right.x)
		{
			return x > right.x;
		}

		return y > right.y;
	}

	//! Returns whether or not this Vector2U is greater than a given right Vector2U in order of x, y, z.
	constexpr bool operator>(const Vector2F& right) const
	{
		if (x != right.x)
		{
			return x > right.x;
		}

		return y > right.y;
	}

	//! Returns whether or not this Vector2U is greater than or equal to a given right Vector2U in order of x, y, z.
	constexpr bool operator>=(const Vector2U& right) const
	{
		if (x != right.x)
		{
			return x >= right.x;
		}

		return y >= right.y;
	}

	//! Returns whether or not this Vector2U is greater than or equal to a given right Vector2U in order of x, y, z.
	constexpr bool operator>=(const Vector2& right) const
	{
		if (x != right.x)
		{
			return x >= right.x;
		}

		return y >= right.y;
	}

	//! Returns whether or not this Vector2U is greater than or equal to a given right Vector2U in order of x, y, z.
	constexpr bool operator>=(const Vector2F& right) const
	{
		if (x != right.x)
		{
			return x >= right.x;
		}

		return y >= right.y;
	}

	//! Returns whether or not this Vector2U is equal to a given right Vector2U.
	constexpr bool operator==(const Vector2U& right) const
	{
		return x == right.x && y == right.y;
	}

	//! Returns whether or not this Vector2U is equal to a given right Vector2U.
	constexpr bool operator==(const Vector2& right) const
	{
		return x == right.x && y == right.y;
	}

	//! Returns whether or not this Vector2U is equal to a given right Vector2U.
	constexpr bool operator==(const Vector2F& right) const
	{
		return x == right.x && y == right.y;
	}

	//! Returns whether or not this Vector2U is not equal to a given right Vector2U.
	constexpr bool operator!=(const Vector2U& right) const
	{
		return !(*this == right);
	}

	//! Returns whether or not this Vector2U is not equal to a given right Vector2U.
	constexpr bool operator!=(const Vector2& right) const
	{
		return !(*this == right);
	}

	//! Returns whether or not this Vector2U is not equal to a given right Vector2U.
	constexpr bool operator!=(const Vector2F& right) const
	{
		return !(*this == right);
	}
};