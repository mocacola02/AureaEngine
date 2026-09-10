//===================================================
// Vector3.h
// Author: Moca 9/10/2026
// Defines a 3D vector type with double precision to
// be used as the basis for most 3D space calculation.
//===================================================
#pragma once

#include "MathFunc.h"

//! 3D (3-element) vector (xyz) type with double precision, used for most 3D space calculation. -Moca
struct Vector3
{
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;

	//===============
	// Constructors
	//===============

	//! Constructs a default Vector3, equal to Zero().
	constexpr Vector3() = default;
	//! Constructs a Vector3 of a given x, y, and z double value.
	constexpr Vector3(const double x, const double y, const double z) : x(x), y(y), z(z) {};


	//=================
	// Static Presets
	//=================

	//! Returns a Vector3 equal to {0.0, 0.0, 0.0}.
	static constexpr Vector3 Zero()
	{
		return {0.0, 0.0, 0.0};
	}

	//! Returns a Vector3 equal to {1.0, 1.0, 1.0}.
	static constexpr Vector3 One()
	{
		return {1.0, 1.0, 1.0};
	}

	//! Returns a Vector3 equal to {1.0, 0.0, 0.0}.
	static constexpr Vector3 Forward()
	{
		return {1.0, 0.0, 0.0};
	}

	//! Returns a Vector3 equal to {0.0, 1.0, 0.0}.
	static constexpr Vector3 Right()
	{
		return {0.0, 1.0, 0.0};
	}

	//! Returns a Vector3 equal to {0.0, 0.0, 1.0}.
	static constexpr Vector3 Up()
	{
		return {0.0, 0.0, 1.0};
	}


	//===============
	// Math Helpers
	//===============

	// Note: This set of functions is inspired by what Godot has available,
	// but no code has been pulled from Godot's source. -Moca

	//! Returns the absolute value (positive value) of this Vector3.
	constexpr Vector3 Abs() const
	{
		return Vector3(
			Math::Abs(x),
			Math::Abs(y),
			Math::Abs(z)
		);
	}

	constexpr double AngleXY() const
	{
		return Math::Atan2(y, x);
	}

	//! Returns the minimum angle to a given Vector3 in radians.
	constexpr double AngleTo(const Vector3& other) const
	{
		return Math::Atan2(Cross(other).Length(), Dot(other));
	}

	//! Returns the direction the cubic Bézier curve is heading at parameter t (its tangent vector).
	constexpr Vector3 BezierDerivative(
		const Vector3& control1, const Vector3& control2,
		const Vector3& end, const double t) const
	{
		const double oneMinusT = 1.0 - t;

		return	(control1 - *this)	  * (3.0 * oneMinusT * oneMinusT) +
				(control2 - control1) * (6.0 * oneMinusT * t) +
				(end - control2)	  * (3.0 * t * t);
	}

	//! Returns the point on the cubic Bézier curve when moving t fraction along it.
	constexpr Vector3 BezierInterpolate(
		const Vector3& control1, const Vector3& control2,
		const Vector3& end, const double t) const
	{
		const double oneMinusT = 1.0 - t;
		const double oneMinusTSquared = oneMinusT * oneMinusT;
		const double tSquared = t * t;

		return	   *this * (oneMinusTSquared * oneMinusT) +
				control1 * (3.0 * oneMinusTSquared * t) +
				control2 * (3.0 * oneMinusT * tSquared) +
					 end * (tSquared * t);
	}

	//! Returns the rounded up value of this Vector3.
	constexpr Vector3 Ceil() const
	{
		return Vector3(Math::Ceil(x), Math::Ceil(y), Math::Ceil(z));
	}

	//! Returns the clamped value of this Vector3 between a given minimum Vector3 and maximum Vector3 value.
	constexpr Vector3 Clamp(const Vector3& min, const Vector3& max) const
	{
		return Vector3(
			Math::Clamp(x, min.x, max.x),
			Math::Clamp(y, min.y, max.y),
			Math::Clamp(z, min.z, max.z)
		);
	}

	//!  Returns the clamped value of this Vector3 between a given minimum double and maximum double value.
	constexpr Vector3 Clamp(const double min, const double max) const
	{
		return Vector3(
			Math::Clamp(x, min, max),
			Math::Clamp(y, min, max),
			Math::Clamp(z, min, max)
		);
	}

	//! Returns the cross product of this Vector3 and another Vector3.
	constexpr Vector3 Cross(const Vector3& other) const
	{
		return Vector3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	//! Returns the interpolated Vector3 using the given weight.
	constexpr Vector3 CubicInterpolate(
		const Vector3& b, const Vector3& preA,
		const Vector3& preB, const double weight) const
	{
		const double weightSquared	= weight * weight;
		const double weightCubed	= weightSquared * weight;

		return  (*this * 2.0 + (b - preA) * weight +
				(preA * 2.0 - *this * 5.0 + b * 4.0 - preB) * weightSquared +
				(-preA + *this * 3.0 - b * 3.0 + preB) * weightCubed) * 0.5;
	}

	//! Returns the normalized Vector3 pointed from this Vector3 to another given Vector3.
	constexpr Vector3 DirectionTo(const Vector3& other) const
	{
		return (other - *this).Normalized();
	}

	//! Returns the squared distance between this Vector3 and another given Vector3.
	constexpr double DistanceSquaredTo(const Vector3& other) const
	{
		return (other - *this).LengthSquared();
	}

	//! Returns the dot product of this Vector3 and another given Vector3.
	constexpr double Dot(const Vector3& other) const
	{
		return	x * other.x +
				y * other.y +
				z * other.z;
	}

	//! Returns the rounded down value of this Vector3.
	constexpr Vector3 Floor() const
	{
		return Vector3(
			Math::Floor(x),
			Math::Floor(y),
			Math::Floor(z)
		);
	}

	//! Returns whether or not this Vector3 is finite.
	constexpr bool IsFinite() const
	{
		return	Math::IsFinite(x) &&
				Math::IsFinite(y) &&
				Math::IsFinite(z);
	}

	//! Returns whether or not this Vector3 is normalized.
	constexpr bool IsNormalized(const double epsilon = 0.00001) const
	{
		return Math::IsEqualApprox(LengthSquared(), 1.0, epsilon);
	}

	//! Returns the squared length of this Vector3.
	constexpr double LengthSquared() const
	{
		return	x * x +
				y * y +
				z * z;
	}

	//! Returns the length of this Vector3.
	constexpr double Length() const
	{
		return Math::Sqrt(LengthSquared());
	}

	//! Returns the point between this Vector3 and a given target Vector3 based on a given weight.
	constexpr Vector3 Lerp(const Vector3& target, const double weight) const
	{
		return Vector3(
			Math::Lerp(x,  target.x, weight),
			Math::Lerp(y,  target.y, weight),
			Math::Lerp(z,  target.z, weight)
		);
	}

	//! Returns the value of this Vector3 with its length limited to a given max length.
	constexpr Vector3 LimitLength(const double maxLength = 1.0) const
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

	//! Returns a Vector3 value where each component is the larger value between this Vector3 and another given Vector3.
	constexpr Vector3 Max(const Vector3& other) const
	{
		return Vector3(
			Math::Max(x, other.x),
			Math::Max(y, other.y),
			Math::Max(z, other.z)
		);
	}

	//! Returns a Vector3 value where each component is the larger value between this Vector3 and a given double value.
	constexpr Vector3 Max(const double value) const
	{
		return Vector3(
			Math::Max(x, value),
			Math::Max(y, value),
			Math::Max(z, value)
		);
	}

	//! Returns a Vector3 value where each component is the smaller value between this Vector3 and another given Vector3.
	constexpr Vector3 Min(const Vector3& other) const
	{
		return Vector3(
			Math::Min(x, other.x),
			Math::Min(y, other.y),
			Math::Min(z, other.z)
		);
	}

	//! Returns a Vector3 value where each component is the smaller value between this Vector3 and a given double value.
	constexpr Vector3 Min(const double value) const
	{
		return Vector3(
			Math::Min(x, value),
			Math::Min(y, value),
			Math::Min(z, value)
		);
	}

	//! Returns the point reached after moving this Vector3 toward another given Vector3 by up to a given delta distance.
	constexpr Vector3 MoveToward(const Vector3& other, const double delta) const
	{
		const Vector3 difference = other - *this;
		const double distance = difference.Length();

		if (distance <= delta || distance == 0.0)
		{
			return other;
		}

		return *this + difference / distance * delta;
	}

	//! Returns the unit-length Vector3 in the same direction as this Vector3.
	constexpr Vector3 Normalized() const
	{
		const double length = Length();

		if (length <= 0.0)
		{
			return Zero();
		}

		return *this / length;
	}

	//! Returns a Vector3 with each component in the range [0, mod] for its corresponding component of a given Vector3 mod value.
	constexpr Vector3 PosMod(const Vector3& mod) const
	{
		return Vector3(
			Math::PosMod(x, mod.x),
			Math::PosMod(y, mod.y),
			Math::PosMod(z, mod.z)
		);
	}

	//! Returns a Vector3 with each component in the range [0, mod] for a given double mod value.
	constexpr Vector3 PosMod(const double mod) const
	{
		return Vector3(
			Math::PosMod(x, mod),
			Math::PosMod(y, mod),
			Math::PosMod(z, mod)
		);
	}

	//! Returns the Vector3 result of projecting this Vector3 onto another given Vector3.
	constexpr Vector3 Project(const Vector3& other) const
	{
		const double denominator = other.LengthSquared();

		if (denominator == 0.0)
		{
			return Vector3();
		}

		return other * (Dot(other) / denominator);
	}

	//! Returns the reflected Vector3 result across a given surface normal Vector3 value.
	constexpr Vector3 Reflect(const Vector3& normal) const
	{
		return *this - normal * (2.0 * Dot(normal));
	}

	//! Returns the rotated Vector3 result around a given axis by a given angle.
	constexpr Vector3 Rotated(const Vector3& axis, const double angle) const
	{
		const Vector3 normalizedAxis = axis.Normalized();
		const double cosine = Math::Cos(angle);
		const double sine	= Math::Sin(angle);

		return *this * cosine + normalizedAxis.Cross(*this) * sine +
				normalizedAxis * (normalizedAxis.Dot(*this) * (1.0 - cosine));
	}

	//! Returns the Vector3 result of rounding this Vector3's components to the nearest whole number (integer).
	constexpr Vector3 Round() const
	{
		return Vector3(
			Math::Round(x),
			Math::Round(y),
			Math::Round(z)
		);
	}

	//! Returns -1 if a component is negative, 0 if zero, and +1 if positive for each component of this Vector3.
	constexpr Vector3 Sign() const
	{
		return Vector3(
			Math::Sign(x),
			Math::Sign(y),
			Math::Sign(z)
		);
	}

	//! Returns the spherical interpolated Vector3 between this Vector and another given Vector3 at a given weight.
	constexpr Vector3 Slerp(const Vector3& other, const double weight) const
	{
		const double startLength = Length();
		const double endLength	 = other.Length();

		if (startLength == 0.0 || endLength == 0.0)
		{
			return Lerp(other, weight);
		}

		const Vector3 start = *this / startLength;
		const Vector3 end	= other / endLength;

		const double dot   = Math::Clamp(start.Dot(end), -1.0, 1.0);
		const double angle = Math::Acos(dot);

		if (Math::IsZeroApprox(angle))
		{
			return Lerp(other, weight);
		}

		const double sine = Math::Sin(angle);
		const double startWeight = Math::Sin((1.0 - weight) * angle) / sine;
		const double endWeight	 = Math::Sin(weight * angle) / sine;

		const Vector3 direction = start * startWeight + end * endWeight;

		const double length = Math::Lerp(startLength, endLength, weight);

		return direction * length;
	}

	//! Returns the Vector3 result from sliding this Vector3 along a surface normal Vector3 value.
	constexpr Vector3 Slide(const Vector3& normal) const
	{
		return *this - normal * Dot(normal);
	}

	//! Returns the Vector3 result of snapping this Vector3's components to the nearest corresponding step value.
	constexpr Vector3 Snapped(const Vector3& step) const
	{
		return Vector3(
			Math::Snapped(x, step.x),
			Math::Snapped(y, step.y),
			Math::Snapped(z, step.z)
		);
	}

	//! Returns the Vector3 result of snapping this Vector3's components to the nearest step value.
	constexpr Vector3 Snapped(const double step) const
	{
		return Vector3(
			Math::Snapped(x, step),
			Math::Snapped(y, step),
			Math::Snapped(z, step)
		);
	}

	// Comparison
	//! Returns whether or not this Vector3 approximately equals a given Vector3 based on a given epsilon value.
	constexpr bool IsEqualApprox(const Vector3& other, const double epsilon = 0.00001) const
	{
		return	Math::IsEqualApprox(x, other.x, epsilon) &&
				Math::IsEqualApprox(y, other.y, epsilon) &&
				Math::IsEqualApprox(z, other.z, epsilon);
	}

	//! Returns whether or not this Vector3 approximately equals zero based on a given epsilon value.
	constexpr bool IsZeroApprox(const double epsilon = 0.00001) const
	{
		return	Math::IsZeroApprox(x, epsilon) &&
				Math::IsZeroApprox(y, epsilon) &&
				Math::IsZeroApprox(z, epsilon);
	}


	//============
	// Operators
	//============

	// Addition
	//! Adds each component of this Vector3 by each component of another given Vector3.
	constexpr Vector3 operator+(const Vector3& other) const
	{
		return Vector3(
			x + other.x,
			y + other.y,
			z + other.z
		);
	}

	//! Adds each component of this Vector3 by each component of another given Vector3.
	constexpr Vector3& operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	// Subtraction
	//! Subtracts each component of this Vector3 by each component of another given Vector3.
	constexpr Vector3 operator-(const Vector3& other) const
	{
		return Vector3(
			x - other.x,
			y - other.y,
			z - other.z
		);
	}

	//! Subtracts each component of this Vector3 by each component of another given Vector3.
	constexpr Vector3& operator-=(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	// Multiplication
	//! Multiplies each component of this Vector3 by each component of another given Vector3.
	constexpr Vector3 operator*(const Vector3& other) const
	{
		return Vector3(
			x * other.x,
			y * other.y,
			z * other.z
		);
	}

	//! Multiplies each component of this Vector3 by each component of another given Vector3.
	constexpr Vector3& operator*=(const Vector3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	//! Multiplies each component of this Vector3 by a given scalar value.
	constexpr Vector3 operator*(const double scalar) const
	{
		return Vector3(
			x * scalar,
			y * scalar,
			z * scalar
		);
	}

	//! Multiplies each component of this Vector3 by a given scalar value.
	constexpr Vector3& operator*=(const double scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return *this;
	}

	// Division
	//! Divides each component of this Vector3 by each component of another given Vector3.
	constexpr Vector3 operator/(const Vector3& other) const
	{
		return Vector3(
			x / other.x,
			y / other.y,
			z / other.z
		);
	}

	//! Divides each component of this Vector3 by each component of another given Vector3.
	constexpr Vector3& operator/=(const Vector3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	//! Divides each component of this Vector3 by a given scalar value.
	constexpr Vector3 operator/(const double scalar) const
	{
		return Vector3(
			x / scalar,
			y / scalar,
			z / scalar
		);
	}

	//! Divides each component of this Vector3 by a given scalar value.
	constexpr Vector3& operator/=(const double scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;

		return *this;
	}

	// Unary
	//! Returns the current value of this Vector3.
	constexpr Vector3 operator+() const
	{
		return *this;
	}

	//! Returns the negative value of this Vector3.
	constexpr Vector3 operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	// Comparison
	//! Returns whether or not this Vector3 is less than a given right Vector3 in order of x, y, z.
	constexpr bool operator<(const Vector3& right) const
	{
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

	//! Returns whether or not this Vector3 is less than or equal to a given right Vector3 in order of x, y, z.
	constexpr bool operator<=(const Vector3& right) const
	{
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

	//! Returns whether or not this Vector3 is greater than a given right Vector3 in order of x, y, z.
	constexpr bool operator>(const Vector3& right) const
	{
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

	//! Returns whether or not this Vector3 is greater than or equal to a given right Vector3 in order of x, y, z.
	constexpr bool operator>=(const Vector3& right) const
	{
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

	//! Returns whether or not this Vector3 is equal to a given right Vector3.
	constexpr bool operator==(const Vector3& right) const
	{
		return x == right.x && y == right.y && z == right.z;
	}

	//! Returns whether or not this Vector3 is not equal to a given right Vector3.
	constexpr bool operator!=(const Vector3& right) const
	{
		return !(*this == right);
	}
};