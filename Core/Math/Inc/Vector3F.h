//===================================================
// Vector3F.h
// Author: Moca 9/10/2026
// Defines a 3D vector type with float precision.
//===================================================
#pragma once

#include "MathFunc.h"

//! 3D (3-element) vector (xyz) type with float precision, used primarily for rendering. -Moca
struct Vector3F
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	//===============
	// Constructors
	//===============

	//! Constructs a default Vector3F, equal to Zero().
	constexpr Vector3F() = default;
	//! Constructs a Vector3F of a given x, y, and z float value.
	constexpr Vector3F(const float x, const float y, const float z) : x(x), y(y), z(z) {}

	//=================
	// Static Presets
	//=================

	//! Returns a Vector3F equal to {0.0, 0.0, 0.0}.
	static constexpr Vector3F Zero()
	{
		return {0.0f, 0.0f, 0.0f};
	}

	//! Returns a Vector3F equal to {1.0, 1.0, 1.0}.
	static constexpr Vector3F One()
	{
		return {1.0f, 1.0f, 1.0f};
	}

	//! Returns a Vector3F equal to {1.0, 0.0, 0.0}.
	static constexpr Vector3F Forward()
	{
		return {1.0f, 0.0f, 0.0f};
	}

	//! Returns a Vector3F equal to {0.0, 1.0, 0.0}.
	static constexpr Vector3F Right()
	{
		return {0.0f, 1.0f, 0.0f};
	}

	//! Returns a Vector3F equal to {0.0, 0.0, 1.0}.
	static constexpr Vector3F Up()
	{
		return {0.0f, 0.0f, 1.0f};
	}


	//===============
	// Math Helpers
	//===============

	// Note: This set of functions is inspired by what Godot has available,
	// but no code has been pulled from Godot's source. -Moca

	//! Returns the absolute value (positive value) of this Vector3F.
	[[nodiscard]] constexpr Vector3F Abs() const
	{
		return {
			Math::AbsF(x),
			Math::AbsF(y),
			Math::AbsF(z)
		};
	}

	[[nodiscard]] constexpr float AngleXY() const
	{
		return Math::Atan2F(y, x);
	}

	//! Returns the minimum angle to a given Vector3F in radians.
	[[nodiscard]] constexpr float AngleTo(const Vector3F& other) const
	{
		return Math::Atan2F(Cross(other).Length(), Dot(other));
	}

	//! Returns the direction the cubic Bézier curve is heading at parameter t (its tangent vector).
	[[nodiscard]] constexpr Vector3F BezierDerivative(
		const Vector3F& control1, const Vector3F& control2,
		const Vector3F& end, const float t) const
	{
		const float oneMinusT = 1.0f - t;

		return	(control1 - *this)	  * (3.0f* oneMinusT * oneMinusT) +
				(control2 - control1) * (6.0f * oneMinusT * t) +
				(end - control2)	  * (3.0f * t * t);
	}

	//! Returns the point on the cubic Bézier curve when moving t fraction along it.
	[[nodiscard]] constexpr Vector3F BezierInterpolate(
		const Vector3F& control1, const Vector3F& control2,
		const Vector3F& end, const float t) const
	{
		const float oneMinusT = 1.0f - t;
		const float oneMinusTSquared = oneMinusT * oneMinusT;
		const float tSquared = t * t;

		return	   *this * (oneMinusTSquared * oneMinusT) +
				control1 * (3.0f * oneMinusTSquared * t) +
				control2 * (3.0f * oneMinusT * tSquared) +
					 end * (tSquared * t);
	}

	//! Returns the rounded up value of this Vector3F.
	[[nodiscard]] constexpr Vector3F Ceil() const
	{
		return {Math::CeilF(x), Math::CeilF(y), Math::CeilF(z)};
	}

	//! Returns the clamped value of this Vector3F between a given minimum Vector3F and maximum Vector3F value.
	[[nodiscard]] constexpr Vector3F Clamp(const Vector3F& min, const Vector3F& max) const
	{
		return {
			Math::ClampF(x, min.x, max.x),
			Math::ClampF(y, min.y, max.y),
			Math::ClampF(z, min.z, max.z)
		};
	}

	//!  Returns the clamped value of this Vector3F between a given minimum float and maximum float value.
	[[nodiscard]] constexpr Vector3F Clamp(const float min, const float max) const
	{
		return {
			Math::ClampF(x, min, max),
			Math::ClampF(y, min, max),
			Math::ClampF(z, min, max)
		};
	}

	//! Returns the cross product of this Vector3F and another Vector3F.
	[[nodiscard]] constexpr Vector3F Cross(const Vector3F& other) const
	{
		return {
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		};
	}

	//! Returns the interpolated Vector3F using the given weight.
	[[nodiscard]] constexpr Vector3F CubicInterpolate(
		const Vector3F& b, const Vector3F& preA,
		const Vector3F& preB, const float weight) const
	{
		const float weightSquared	= weight * weight;
		const float weightCubed	= weightSquared * weight;

		return  (*this * 2.0f + (b - preA) * weight +
				(preA * 2.0f - *this * 5.0f + b * 4.0f - preB) * weightSquared +
				(-preA + *this * 3.0f - b * 3.0f + preB) * weightCubed) * 0.5f;
	}

	//! Returns the normalized Vector3F pointed from this Vector3F to another given Vector3F.
	[[nodiscard]] constexpr Vector3F DirectionTo(const Vector3F& other) const
	{
		return (other - *this).Normalized();
	}

	//! Returns the squared distance between this Vector3F and another given Vector3F.
	[[nodiscard]] constexpr float DistanceSquaredTo(const Vector3F& other) const
	{
		return (other - *this).LengthSquared();
	}

	//! Returns the dot product of this Vector3F and another given Vector3F.
	[[nodiscard]] constexpr float Dot(const Vector3F& other) const
	{
		return	x * other.x +
				y * other.y +
				z * other.z;
	}

	//! Returns the rounded down value of this Vector3F.
	[[nodiscard]] constexpr Vector3F Floor() const
	{
		return {
			Math::FloorF(x),
			Math::FloorF(y),
			Math::FloorF(z)
		};
	}

	//! Returns whether or not this Vector3F is finite.
	[[nodiscard]] constexpr bool IsFinite() const
	{
		return	Math::IsFiniteF(x) &&
				Math::IsFiniteF(y) &&
				Math::IsFiniteF(z);
	}

	//! Returns whether or not this Vector3F is normalized.
	[[nodiscard]] constexpr bool IsNormalized(const float epsilon = 0.00001f) const
	{
		return Math::IsEqualApproxF(LengthSquared(), 1.0f, epsilon);
	}

	//! Returns the squared length of this Vector3F.
	[[nodiscard]] constexpr float LengthSquared() const
	{
		return	x * x +
				y * y +
				z * z;
	}

	//! Returns the length of this Vector3F.
	[[nodiscard]] constexpr float Length() const
	{
		return Math::SqrtF(LengthSquared());
	}

	//! Returns the point between this Vector3F and a given target Vector3F based on a given weight.
	[[nodiscard]] constexpr Vector3F Lerp(const Vector3F& target, const float weight) const
	{
		return {
			Math::LerpF(x,  target.x, weight),
			Math::LerpF(y,  target.y, weight),
			Math::LerpF(z,  target.z, weight)
		};
	}

	//! Returns the value of this Vector3F with its length limited to a given max length.
	[[nodiscard]] constexpr Vector3F LimitLength(const float maxLength = 1.0f) const
	{
		const float lengthSquared = LengthSquared();

		if (const float maxLengthSquared = maxLength * maxLength; lengthSquared <= maxLengthSquared)
		{
			return *this;
		}

		const float scale = maxLength / Math::SqrtF(lengthSquared);

		return *this * scale;
	}

	//! Returns a Vector3F value where each component is the larger value between this Vector3F and another given Vector3F.
	[[nodiscard]] constexpr Vector3F Max(const Vector3F& other) const
	{
		return {
			Math::MaxF(x, other.x),
			Math::MaxF(y, other.y),
			Math::MaxF(z, other.z)
		};
	}

	//! Returns a Vector3F value where each component is the larger value between this Vector3F and a given float value.
	[[nodiscard]] constexpr Vector3F Max(const float value) const
	{
		return {
			Math::MaxF(x, value),
			Math::MaxF(y, value),
			Math::MaxF(z, value)
		};
	}

	//! Returns a Vector3F value where each component is the smaller value between this Vector3F and another given Vector3F.
	[[nodiscard]] constexpr Vector3F Min(const Vector3F& other) const
	{
		return {
			Math::MinF(x, other.x),
			Math::MinF(y, other.y),
			Math::MinF(z, other.z)
		};
	}

	//! Returns a Vector3F value where each component is the smaller value between this Vector3F and a given float value.
	[[nodiscard]] constexpr Vector3F Min(const float value) const
	{
		return {
			Math::MinF(x, value),
			Math::MinF(y, value),
			Math::MinF(z, value)
		};
	}

	//! Returns the point reached after moving this Vector3F toward another given Vector3F by up to a given delta distance.
	[[nodiscard]] constexpr Vector3F MoveToward(const Vector3F& other, const float delta) const
	{
		const Vector3F difference = other - *this;
		const float distance = difference.Length();

		if (distance <= delta || distance == 0.0f)
		{
			return other;
		}

		return *this + difference / distance * delta;
	}

	//! Returns the unit-length Vector3F in the same direction as this Vector3F.
	[[nodiscard]] constexpr Vector3F Normalized() const
	{
		const float length = Length();

		if (length <= 0.0f)
		{
			return Zero();
		}

		return *this / length;
	}

	//! Returns a Vector3F with each component in the range [0, mod] for its corresponding component of a given Vector3F mod value.
	[[nodiscard]] constexpr Vector3F PosMod(const Vector3F& mod) const
	{
		return {
			Math::PosModF(x, mod.x),
			Math::PosModF(y, mod.y),
			Math::PosModF(z, mod.z)
		};
	}

	//! Returns a Vector3F with each component in the range [0, mod] for a given float mod value.
	[[nodiscard]] constexpr Vector3F PosMod(const float mod) const
	{
		return {
			Math::PosModF(x, mod),
			Math::PosModF(y, mod),
			Math::PosModF(z, mod)
		};
	}

	//! Returns the Vector3F result of projecting this Vector3F onto another given Vector3F.
	[[nodiscard]] constexpr Vector3F Project(const Vector3F& other) const
	{
		const float denominator = other.LengthSquared();

		if (denominator == 0.0f)
		{
			return {};
		}

		return other * (Dot(other) / denominator);
	}

	//! Returns the reflected Vector3F result across a given surface normal Vector3F value.
	[[nodiscard]] constexpr Vector3F Reflect(const Vector3F& normal) const
	{
		return *this - normal * (2.0f * Dot(normal));
	}

	//! Returns the rotated Vector3F result around a given axis by a given angle.
	[[nodiscard]] constexpr Vector3F Rotated(const Vector3F& axis, const float angle) const
	{
		const Vector3F normalizedAxis = axis.Normalized();
		const float cosine = Math::CosF(angle);
		const float sine	= Math::SinF(angle);

		return *this * cosine + normalizedAxis.Cross(*this) * sine +
				normalizedAxis * (normalizedAxis.Dot(*this) * (1.0f - cosine));
	}

	//! Returns the Vector3F result of rounding this Vector3F's components to the nearest whole number (integer).
	[[nodiscard]] constexpr Vector3F Round() const
	{
		return {
			Math::RoundF(x),
			Math::RoundF(y),
			Math::RoundF(z)
		};
	}

	//! Returns -1 if a component is negative, 0 if zero, and +1 if positive for each component of this Vector3F.
	[[nodiscard]] constexpr Vector3F Sign() const
	{
		return {
			Math::SignF(x),
			Math::SignF(y),
			Math::SignF(z)
		};
	}

	//! Returns the spherical interpolated Vector3F between this Vector and another given Vector3F at a given weight.
	[[nodiscard]] constexpr Vector3F Slerp(const Vector3F& other, const float weight) const
	{
		const float startLength = Length();
		const float endLength	 = other.Length();

		if (startLength == 0.0f || endLength == 0.0f)
		{
			return Lerp(other, weight);
		}

		const Vector3F start = *this / startLength;
		const Vector3F end	= other / endLength;

		const float dot   = Math::ClampF(start.Dot(end), -1.0f, 1.0f);
		const float angle = Math::AcosF(dot);

		if (Math::IsZeroApproxF(angle))
		{
			return Lerp(other, weight);
		}

		const float sine = Math::SinF(angle);
		const float startWeight = Math::SinF((1.0f - weight) * angle) / sine;
		const float endWeight	 = Math::SinF(weight * angle) / sine;

		const Vector3F direction = start * startWeight + end * endWeight;

		const float length = Math::LerpF(startLength, endLength, weight);

		return direction * length;
	}

	//! Returns the Vector3F result from sliding this Vector3F along a surface normal Vector3F value.
	[[nodiscard]] constexpr Vector3F Slide(const Vector3F& normal) const
	{
		return *this - normal * Dot(normal);
	}

	//! Returns the Vector3F result of snapping this Vector3F's components to the nearest corresponding step value.
	[[nodiscard]] constexpr Vector3F Snapped(const Vector3F& step) const
	{
		return {
			Math::SnappedF(x, step.x),
			Math::SnappedF(y, step.y),
			Math::SnappedF(z, step.z)
		};
	}

	//! Returns the Vector3F result of snapping this Vector3F's components to the nearest step value.
	[[nodiscard]] constexpr Vector3F Snapped(const float step) const
	{
		return {
			Math::SnappedF(x, step),
			Math::SnappedF(y, step),
			Math::SnappedF(z, step)
		};
	}

	// Comparison
	//! Returns whether or not this Vector3F approximately equals a given Vector3F based on a given epsilon value.
	[[nodiscard]] constexpr bool IsEqualApprox(const Vector3F& other, const float epsilon = 0.00001f) const
	{
		return	Math::IsEqualApproxF(x, other.x, epsilon) &&
				Math::IsEqualApproxF(y, other.y, epsilon) &&
				Math::IsEqualApproxF(z, other.z, epsilon);
	}

	//! Returns whether or not this Vector3F approximately equals zero based on a given epsilon value.
	[[nodiscard]] constexpr bool IsZeroApprox(const float epsilon = 0.00001f) const
	{
		return	Math::IsZeroApproxF(x, epsilon) &&
				Math::IsZeroApproxF(y, epsilon) &&
				Math::IsZeroApproxF(z, epsilon);
	}


	//============
	// Operators
	//============

	// Addition
	//! Adds each component of this Vector3F by each component of another given Vector3F.
	constexpr Vector3F operator+(const Vector3F& other) const
	{
		return {
			x + other.x,
			y + other.y,
			z + other.z
		};
	}

	//! Adds each component of this Vector3F by each component of another given Vector3F.
	constexpr Vector3F& operator+=(const Vector3F& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	// Subtraction
	//! Subtracts each component of this Vector3F by each component of another given Vector3F.
	constexpr Vector3F operator-(const Vector3F& other) const
	{
		return {
			x - other.x,
			y - other.y,
			z - other.z
		};
	}

	//! Subtracts each component of this Vector3F by each component of another given Vector3F.
	constexpr Vector3F& operator-=(const Vector3F& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	// Multiplication
	//! Multiplies each component of this Vector3F by each component of another given Vector3F.
	constexpr Vector3F operator*(const Vector3F& other) const
	{
		return {
			x * other.x,
			y * other.y,
			z * other.z
		};
	}

	//! Multiplies each component of this Vector3F by each component of another given Vector3F.
	constexpr Vector3F& operator*=(const Vector3F& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	//! Multiplies each component of this Vector3F by a given scalar value.
	constexpr Vector3F operator*(const float scalar) const
	{
		return {
			x * scalar,
			y * scalar,
			z * scalar
		};
	}

	//! Multiplies each component of this Vector3F by a given scalar value.
	constexpr Vector3F& operator*=(const float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return *this;
	}

	// Division
	//! Divides each component of this Vector3F by each component of another given Vector3F.
	constexpr Vector3F operator/(const Vector3F& other) const
	{
		return {
			x / other.x,
			y / other.y,
			z / other.z
		};
	}

	//! Divides each component of this Vector3F by each component of another given Vector3F.
	constexpr Vector3F& operator/=(const Vector3F& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	//! Divides each component of this Vector3F by a given scalar value.
	constexpr Vector3F operator/(const float scalar) const
	{
		return {
			x / scalar,
			y / scalar,
			z / scalar
		};
	}

	//! Divides each component of this Vector3F by a given scalar value.
	constexpr Vector3F& operator/=(const float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;

		return *this;
	}

	// Unary
	//! Returns the current value of this Vector3F.
	constexpr Vector3F operator+() const
	{
		return *this;
	}

	//! Returns the negative value of this Vector3F.
	constexpr Vector3F operator-() const
	{
		return {-x, -y, -z};
	}

	// Comparison
	//! Returns whether or not this Vector3F is less than a given right Vector3F in order of x, y, z.
	constexpr bool operator<(const Vector3F& right) const
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

	//! Returns whether or not this Vector3F is less than or equal to a given right Vector3F in order of x, y, z.
	constexpr bool operator<=(const Vector3F& right) const
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

	//! Returns whether or not this Vector3F is greater than a given right Vector3F in order of x, y, z.
	constexpr bool operator>(const Vector3F& right) const
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

	//! Returns whether or not this Vector3F is greater than or equal to a given right Vector3F in order of x, y, z.
	constexpr bool operator>=(const Vector3F& right) const
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

	//! Returns whether or not this Vector3F is equal to a given right Vector3F.
	constexpr bool operator==(const Vector3F& right) const
	{
		return x == right.x && y == right.y && z == right.z;
	}

	//! Returns whether or not this Vector3F is not equal to a given right Vector3F.
	constexpr bool operator!=(const Vector3F& right) const
	{
		return !(*this == right);
	}
};