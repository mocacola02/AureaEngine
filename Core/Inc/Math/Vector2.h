//===================================================
// Vector2.h
// Author: Moca 9/29/2026
// Defines a 2D vector type with double precision to
// be used as the basis for most 2D space calculation.
//===================================================
#pragma once

#include "MathFunc.h"

//! 2D (2-element) vector (xy) type with double precision, used for most 2D space calculation. -Moca
struct Vector2
{
	double x = 0.0;
	double y = 0.0;

	//===============
	// Constructors
	//===============

	//! Constructs a default Vector2, equal to Zero().
	constexpr Vector2() = default;
	//! Constructs a Vector2 of a given x and y double value.
	constexpr Vector2(const double x, const double y) : x(x), y(y) {}

	//=================
	// Static Presets
	//=================

	//! Returns a Vector2 equal to {0.0, 0.0}.
	static constexpr Vector2 Zero()
	{
		return {0.0, 0.0};
	}

	//! Returns a Vector2 equal to {1.0, 1.0}.
	static constexpr Vector2 One()
	{
		return {1.0, 1.0};
	}

	//! Returns a Vector2 equal to {1.0, 0.0}.
	static constexpr Vector2 Right()
	{
		return {1.0, 0.0};
	}

	//! Returns a Vector2 equal to {0.0, 1.0}.
	static constexpr Vector2 Up()
	{
		return {0.0, 1.0};
	}


	//===============
	// Math Helpers
	//===============

	// Note: This set of functions is inspired by what Godot has available,
	// but no code has been pulled from Godot's source. -Moca

	//! Returns the absolute value (positive value) of this Vector2.
	[[nodiscard]] constexpr Vector2 Abs() const
	{
		return {
			Math::Abs(x),
			Math::Abs(y)
		};
	}

	[[nodiscard]] constexpr double AngleXY() const
	{
		return Math::Atan2(y, x);
	}

	//! Returns the minimum angle to a given Vector2 in radians.
	[[nodiscard]] constexpr double AngleTo(const Vector2& other) const
	{
		return Math::Atan2(Math::Abs(Cross(other)), Dot(other));
	}

	//! Returns the direction the cubic Bézier curve is heading at parameter t (its tangent vector).
	[[nodiscard]] constexpr Vector2 BezierDerivative(
		const Vector2& control1, const Vector2& control2,
		const Vector2& end, const double t) const
	{
		const double oneMinusT = 1.0 - t;

		return	(control1 - *this)	  * (3.0 * oneMinusT * oneMinusT) +
				(control2 - control1) * (6.0 * oneMinusT * t) +
				(end - control2)	  * (3.0 * t * t);
	}

	//! Returns the point on the cubic Bézier curve when moving t fraction along it.
	[[nodiscard]] constexpr Vector2 BezierInterpolate(
		const Vector2& control1, const Vector2& control2,
		const Vector2& end, const double t) const
	{
		const double oneMinusT = 1.0 - t;
		const double oneMinusTSquared = oneMinusT * oneMinusT;
		const double tSquared = t * t;

		return	   *this * (oneMinusTSquared * oneMinusT) +
				control1 * (3.0 * oneMinusTSquared * t) +
				control2 * (3.0 * oneMinusT * tSquared) +
					 end * (tSquared * t);
	}

	//! Returns the rounded up value of this Vector2.
	[[nodiscard]] constexpr Vector2 Ceil() const
	{
		return {Math::Ceil(x), Math::Ceil(y)};
	}

	//! Returns the clamped value of this Vector2 between a given minimum Vector2 and maximum Vector2 value.
	[[nodiscard]] constexpr Vector2 Clamp(const Vector2& min, const Vector2& max) const
	{
		return {
			Math::Clamp(x, min.x, max.x),
			Math::Clamp(y, min.y, max.y)
		};
	}

	//!  Returns the clamped value of this Vector2 between a given minimum double and maximum double value.
	[[nodiscard]] constexpr Vector2 Clamp(const double min, const double max) const
	{
		return {
			Math::Clamp(x, min, max),
			Math::Clamp(y, min, max)
		};
	}

	//! Returns the cross product of this Vector2 and another Vector2.
	[[nodiscard]] constexpr double Cross(const Vector2& other) const
	{
		return x * other.y - y * other.x;
	}

	//! Returns the interpolated Vector2 using the given weight.
	[[nodiscard]] constexpr Vector2 CubicInterpolate(
		const Vector2& b, const Vector2& preA,
		const Vector2& preB, const double weight) const
	{
		const double weightSquared	= weight * weight;
		const double weightCubed	= weightSquared * weight;

		return  (*this * 2.0 + (b - preA) * weight +
				(preA * 2.0 - *this * 5.0 + b * 4.0 - preB) * weightSquared +
				(-preA + *this * 3.0 - b * 3.0 + preB) * weightCubed) * 0.5;
	}

	//! Returns the normalized Vector2 pointed from this Vector2 to another given Vector2.
	[[nodiscard]] constexpr Vector2 DirectionTo(const Vector2& other) const
	{
		return (other - *this).Normalized();
	}

	//! Returns the squared distance between this Vector2 and another given Vector2.
	[[nodiscard]] constexpr double DistanceSquaredTo(const Vector2& other) const
	{
		return (other - *this).LengthSquared();
	}

	//! Returns the dot product of this Vector2 and another given Vector2.
	[[nodiscard]] constexpr double Dot(const Vector2& other) const
	{
		return	x * other.x + y * other.y;
	}

	//! Returns the rounded down value of this Vector2.
	[[nodiscard]] constexpr Vector2 Floor() const
	{
		return {
			Math::Floor(x),
			Math::Floor(y)
		};
	}

	//! Returns whether or not this Vector2 is finite.
	[[nodiscard]] constexpr bool IsFinite() const
	{
		return Math::IsFinite(x) && Math::IsFinite(y);
	}

	//! Returns whether or not this Vector2 is normalized.
	[[nodiscard]] constexpr bool IsNormalized(const double epsilon = 0.00001) const
	{
		return Math::IsEqualApprox(LengthSquared(), 1.0, epsilon);
	}

	//! Returns the squared length of this Vector2.
	[[nodiscard]] constexpr double LengthSquared() const
	{
		return	x * x + y * y;
	}

	//! Returns the length of this Vector2.
	[[nodiscard]] constexpr double Length() const
	{
		return Math::Sqrt(LengthSquared());
	}

	//! Returns the point between this Vector2 and a given target Vector2 based on a given weight.
	[[nodiscard]] constexpr Vector2 Lerp(const Vector2& target, const double weight) const
	{
		return {
			Math::Lerp(x,  target.x, weight),
			Math::Lerp(y,  target.y, weight)
		};
	}

	//! Returns the value of this Vector2 with its length limited to a given max length.
	[[nodiscard]] constexpr Vector2 LimitLength(const double maxLength = 1.0) const
	{
		const double lengthSquared = LengthSquared();

		if (const double maxLengthSquared = maxLength * maxLength; lengthSquared <= maxLengthSquared)
		{
			return *this;
		}

		const double scale = maxLength / Math::Sqrt(lengthSquared);

		return *this * scale;
	}

	//! Returns a Vector2 value where each component is the larger value between this Vector2 and another given Vector2.
	[[nodiscard]] constexpr Vector2 Max(const Vector2& other) const
	{
		return {
			Math::Max(x, other.x),
			Math::Max(y, other.y)
		};
	}

	//! Returns a Vector2 value where each component is the larger value between this Vector2 and a given double value.
	[[nodiscard]] constexpr Vector2 Max(const double value) const
	{
		return {
			Math::Max(x, value),
			Math::Max(y, value)
		};
	}

	//! Returns a Vector2 value where each component is the smaller value between this Vector2 and another given Vector2.
	[[nodiscard]] constexpr Vector2 Min(const Vector2& other) const
	{
		return {
			Math::Min(x, other.x),
			Math::Min(y, other.y)
		};
	}

	//! Returns a Vector2 value where each component is the smaller value between this Vector2 and a given double value.
	[[nodiscard]] constexpr Vector2 Min(const double value) const
	{
		return {
			Math::Min(x, value),
			Math::Min(y, value)
		};
	}

	//! Returns the point reached after moving this Vector2 toward another given Vector2 by up to a given delta distance.
	[[nodiscard]] constexpr Vector2 MoveToward(const Vector2& other, const double delta) const
	{
		const Vector2 difference = other - *this;
		const double distance = difference.Length();

		if (distance <= delta || distance == 0.0)
		{
			return other;
		}

		return *this + difference / distance * delta;
	}

	//! Returns the unit-length Vector2 in the same direction as this Vector2.
	[[nodiscard]] constexpr Vector2 Normalized() const
	{
		const double length = Length();

		if (length <= 0.0)
		{
			return Zero();
		}

		return *this / length;
	}

	//! Returns a Vector2 with each component in the range [0, mod] for its corresponding component of a given Vector2 mod value.
	[[nodiscard]] constexpr Vector2 PosMod(const Vector2& mod) const
	{
		return {
			Math::PosMod(x, mod.x),
			Math::PosMod(y, mod.y)
		};
	}

	//! Returns a Vector2 with each component in the range [0, mod] for a given double mod value.
	[[nodiscard]] constexpr Vector2 PosMod(const double mod) const
	{
		return {
			Math::PosMod(x, mod),
			Math::PosMod(y, mod)
		};
	}

	//! Returns the Vector2 result of projecting this Vector2 onto another given Vector2.
	[[nodiscard]] constexpr Vector2 Project(const Vector2& other) const
	{
		const double denominator = other.LengthSquared();

		if (denominator == 0.0)
		{
			return {};
		}

		return other * (Dot(other) / denominator);
	}

	//! Returns the reflected Vector2 result across a given surface normal Vector2 value.
	[[nodiscard]] constexpr Vector2 Reflect(const Vector2& normal) const
	{
		return *this - normal * (2.0 * Dot(normal));
	}

	//! Returns the rotated Vector2 result around a given axis by a given angle.
	[[nodiscard]] constexpr Vector2 Rotated(const double angle) const
	{
		const double c = Math::Cos(angle);
		const double s = Math::Sin(angle);

		return {
			x * c - y * s,
			x * s + y * c
		};
	}

	//! Returns the Vector2 result of rounding this Vector2's components to the nearest whole number (integer).
	[[nodiscard]] constexpr Vector2 Round() const
	{
		return {
			Math::Round(x),
			Math::Round(y)
		};
	}

	//! Returns -1 if a component is negative, 0 if zero, and +1 if positive for each component of this Vector2.
	[[nodiscard]] constexpr Vector2 Sign() const
	{
		return {
			Math::Sign(x),
			Math::Sign(y)
		};
	}

	//! Returns the spherical interpolated Vector2 between this Vector and another given Vector2 at a given weight.
	[[nodiscard]] constexpr Vector2 Slerp(const Vector2& other, const double weight) const
	{
		const double startLength = Length();
		const double endLength	 = other.Length();

		if (startLength == 0.0 || endLength == 0.0)
		{
			return Lerp(other, weight);
		}

		const Vector2 start = *this / startLength;
		const Vector2 end	= other / endLength;

		const double dot   = Math::Clamp(start.Dot(end), -1.0, 1.0);
		const double angle = Math::Acos(dot);

		if (Math::IsZeroApprox(angle))
		{
			return Lerp(other, weight);
		}

		const double sine = Math::Sin(angle);
		const double startWeight = Math::Sin((1.0 - weight) * angle) / sine;
		const double endWeight	 = Math::Sin(weight * angle) / sine;

		const Vector2 direction = start * startWeight + end * endWeight;

		const double length = Math::Lerp(startLength, endLength, weight);

		return direction * length;
	}

	//! Returns the Vector2 result from sliding this Vector2 along a surface normal Vector2 value.
	[[nodiscard]] constexpr Vector2 Slide(const Vector2& normal) const
	{
		return *this - normal * Dot(normal);
	}

	//! Returns the Vector2 result of snapping this Vector2's components to the nearest corresponding step value.
	[[nodiscard]] constexpr Vector2 Snapped(const Vector2& step) const
	{
		return {
			Math::Snapped(x, step.x),
			Math::Snapped(y, step.y)
		};
	}

	//! Returns the Vector2 result of snapping this Vector2's components to the nearest step value.
	[[nodiscard]] constexpr Vector2 Snapped(const double step) const
	{
		return {
			Math::Snapped(x, step),
			Math::Snapped(y, step)
		};
	}

	// Comparison
	//! Returns whether or not this Vector2 approximately equals a given Vector2 based on a given epsilon value.
	[[nodiscard]] constexpr bool IsEqualApprox(const Vector2& other, const double epsilon = 0.00001) const
	{
		return	Math::IsEqualApprox(x, other.x, epsilon) &&
				Math::IsEqualApprox(y, other.y, epsilon);
	}

	//! Returns whether or not this Vector2 approximately equals zero based on a given epsilon value.
	[[nodiscard]] constexpr bool IsZeroApprox(const double epsilon = 0.00001) const
	{
		return	Math::IsZeroApprox(x, epsilon) &&
				Math::IsZeroApprox(y, epsilon);
	}


	//============
	// Operators
	//============

	// Addition
	//! Adds each component of this Vector2 by each component of another given Vector2.
	constexpr Vector2 operator+(const Vector2& other) const
	{
		return {
			x + other.x,
			y + other.y
		};
	}

	//! Adds each component of this Vector2 by each component of another given Vector2.
	constexpr Vector2& operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	// Subtraction
	//! Subtracts each component of this Vector2 by each component of another given Vector2.
	constexpr Vector2 operator-(const Vector2& other) const
	{
		return {
			x - other.x,
			y - other.y
		};
	}

	//! Subtracts each component of this Vector2 by each component of another given Vector2.
	constexpr Vector2& operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	// Multiplication
	//! Multiplies each component of this Vector2 by each component of another given Vector2.
	constexpr Vector2 operator*(const Vector2& other) const
	{
		return {
			x * other.x,
			y * other.y
		};
	}

	//! Multiplies each component of this Vector2 by each component of another given Vector2.
	constexpr Vector2& operator*=(const Vector2& other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	//! Multiplies each component of this Vector2 by a given scalar value.
	constexpr Vector2 operator*(const double scalar) const
	{
		return {
			x * scalar,
			y * scalar
		};
	}

	//! Multiplies each component of this Vector2 by a given scalar value.
	constexpr Vector2& operator*=(const double scalar)
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}

	// Division
	//! Divides each component of this Vector2 by each component of another given Vector2.
	constexpr Vector2 operator/(const Vector2& other) const
	{
		return {
			x / other.x,
			y / other.y
		};
	}

	//! Divides each component of this Vector2 by each component of another given Vector2.
	constexpr Vector2& operator/=(const Vector2& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	//! Divides each component of this Vector2 by a given scalar value.
	constexpr Vector2 operator/(const double scalar) const
	{
		return {
			x / scalar,
			y / scalar
		};
	}

	//! Divides each component of this Vector2 by a given scalar value.
	constexpr Vector2& operator/=(const double scalar)
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}

	// Unary
	//! Returns the current value of this Vector2.
	constexpr Vector2 operator+() const
	{
		return *this;
	}

	//! Returns the negative value of this Vector2.
	constexpr Vector2 operator-() const
	{
		return {-x, -y};
	}

	// Comparison
	//! Returns whether or not this Vector2 is less than a given right Vector2 in order of x, y, z.
	constexpr bool operator<(const Vector2& right) const
	{
		if (x != right.x)
		{
			return x < right.x;
		}

		return y < right.y;
	}

	//! Returns whether or not this Vector2 is less than or equal to a given right Vector2 in order of x, y, z.
	constexpr bool operator<=(const Vector2& right) const
	{
		if (x != right.x)
		{
			return x <= right.x;
		}

		return y <= right.y;
	}

	//! Returns whether or not this Vector2 is greater than a given right Vector2 in order of x, y, z.
	constexpr bool operator>(const Vector2& right) const
	{
		if (x != right.x)
		{
			return x > right.x;
		}

		return y > right.y;
	}

	//! Returns whether or not this Vector2 is greater than or equal to a given right Vector2 in order of x, y, z.
	constexpr bool operator>=(const Vector2& right) const
	{
		if (x != right.x)
		{
			return x >= right.x;
		}

		return y >= right.y;
	}

	//! Returns whether or not this Vector2 is equal to a given right Vector2.
	constexpr bool operator==(const Vector2& right) const
	{
		return x == right.x && y == right.y;
	}

	//! Returns whether or not this Vector2 is not equal to a given right Vector2.
	constexpr bool operator!=(const Vector2& right) const
	{
		return !(*this == right);
	}
};