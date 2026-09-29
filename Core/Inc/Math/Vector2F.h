//===================================================
// Vector2F.h
// Author: Moca 9/29/2026
// Defines a 2D vector type with float precision.
//===================================================
#pragma once

#include "MathFunc.h"

//! 2D (2-element) vector (xy) type with float precision. -Moca
struct Vector2F
{
	float x = 0.0f;
	float y = 0.0f;

	//===============
	// Constructors
	//===============

	//! Constructs a default Vector2F, equal to Zero().
	constexpr Vector2F() = default;
	//! Constructs a Vector2F of a given x and y float value.
	constexpr Vector2F(const float x, const float y) : x(x), y(y) {}

	//=================
	// Static Presets
	//=================

	//! Returns a Vector2F equal to {0.0, 0.0}.
	static constexpr Vector2F Zero()
	{
		return {0.0f, 0.0f};
	}

	//! Returns a Vector2F equal to {1.0, 1.0}.
	static constexpr Vector2F One()
	{
		return {1.0f, 1.0f};
	}

	//! Returns a Vector2F equal to {1.0, 0.0}.
	static constexpr Vector2F Right()
	{
		return {1.0f, 0.0f};
	}

	//! Returns a Vector2F equal to {0.0, 1.0}.
	static constexpr Vector2F Up()
	{
		return {0.0f, 1.0f};
	}


	//===============
	// Math Helpers
	//===============

	// Note: This set of functions is inspired by what Godot has available,
	// but no code has been pulled from Godot's source. -Moca

	//! Returns the absolute value (positive value) of this Vector2F.
	[[nodiscard]] constexpr Vector2F Abs() const
	{
		return {
			Math::AbsF(x),
			Math::AbsF(y)
		};
	}

	[[nodiscard]] constexpr float AngleXY() const
	{
		return Math::Atan2F(y, x);
	}

	//! Returns the minimum angle to a given Vector2F in radians.
	[[nodiscard]] constexpr float AngleTo(const Vector2F& other) const
	{
		return Math::Atan2F(Math::AbsF(Cross(other)), Dot(other));
	}

	//! Returns the direction the cubic Bézier curve is heading at parameter t (its tangent vector).
	[[nodiscard]] constexpr Vector2F BezierDerivative(
		const Vector2F& control1, const Vector2F& control2,
		const Vector2F& end, const float t) const
	{
		const float oneMinusT = 1.0f - t;

		return	(control1 - *this)	  * (3.0f * oneMinusT * oneMinusT) +
				(control2 - control1) * (6.0f * oneMinusT * t) +
				(end - control2)	  * (3.0f * t * t);
	}

	//! Returns the point on the cubic Bézier curve when moving t fraction along it.
	[[nodiscard]] constexpr Vector2F BezierInterpolate(
		const Vector2F& control1, const Vector2F& control2,
		const Vector2F& end, const float t) const
	{
		const float oneMinusT = 1.0f - t;
		const float oneMinusTSquared = oneMinusT * oneMinusT;
		const float tSquared = t * t;

		return	   *this * (oneMinusTSquared * oneMinusT) +
				control1 * (3.0f * oneMinusTSquared * t) +
				control2 * (3.0f * oneMinusT * tSquared) +
					 end * (tSquared * t);
	}

	//! Returns the rounded up value of this Vector2F.
	[[nodiscard]] constexpr Vector2F Ceil() const
	{
		return {Math::CeilF(x), Math::CeilF(y)};
	}

	//! Returns the clamped value of this Vector2F between a given minimum Vector2F and maximum Vector2F value.
	[[nodiscard]] constexpr Vector2F Clamp(const Vector2F& min, const Vector2F& max) const
	{
		return {
			Math::ClampF(x, min.x, max.x),
			Math::ClampF(y, min.y, max.y)
		};
	}

	//!  Returns the clamped value of this Vector2F between a given minimum float and maximum float value.
	[[nodiscard]] constexpr Vector2F Clamp(const float min, const float max) const
	{
		return {
			Math::ClampF(x, min, max),
			Math::ClampF(y, min, max)
		};
	}

	//! Returns the cross product of this Vector2F and another Vector2F.
	[[nodiscard]] constexpr float Cross(const Vector2F& other) const
	{
		return x * other.y - y * other.x;
	}

	//! Returns the interpolated Vector2F using the given weight.
	[[nodiscard]] constexpr Vector2F CubicInterpolate(
		const Vector2F& b, const Vector2F& preA,
		const Vector2F& preB, const float weight) const
	{
		const float weightSquared	= weight * weight;
		const float weightCubed	= weightSquared * weight;

		return  (*this * 2.0f + (b - preA) * weight +
				(preA * 2.0f - *this * 5.0f + b * 4.0f - preB) * weightSquared +
				(-preA + *this * 3.0f - b * 3.0f + preB) * weightCubed) * 0.5f;
	}

	//! Returns the normalized Vector2F pointed from this Vector2F to another given Vector2F.
	[[nodiscard]] constexpr Vector2F DirectionTo(const Vector2F& other) const
	{
		return (other - *this).Normalized();
	}

	//! Returns the squared distance between this Vector2F and another given Vector2F.
	[[nodiscard]] constexpr float DistanceSquaredTo(const Vector2F& other) const
	{
		return (other - *this).LengthSquared();
	}

	//! Returns the dot product of this Vector2F and another given Vector2F.
	[[nodiscard]] constexpr float Dot(const Vector2F& other) const
	{
		return	x * other.x + y * other.y;
	}

	//! Returns the rounded down value of this Vector2F.
	[[nodiscard]] constexpr Vector2F Floor() const
	{
		return {
			Math::FloorF(x),
			Math::FloorF(y)
		};
	}

	//! Returns whether or not this Vector2F is finite.
	[[nodiscard]] constexpr bool IsFinite() const
	{
		return Math::IsFiniteF(x) && Math::IsFiniteF(y);
	}

	//! Returns whether or not this Vector2F is normalized.
	[[nodiscard]] constexpr bool IsNormalized(const float epsilon = 0.00001f) const
	{
		return Math::IsEqualApproxF(LengthSquared(), 1.0f, epsilon);
	}

	//! Returns the squared length of this Vector2F.
	[[nodiscard]] constexpr float LengthSquared() const
	{
		return	x * x + y * y;
	}

	//! Returns the length of this Vector2F.
	[[nodiscard]] constexpr float Length() const
	{
		return Math::SqrtF(LengthSquared());
	}

	//! Returns the point between this Vector2F and a given target Vector2F based on a given weight.
	[[nodiscard]] constexpr Vector2F Lerp(const Vector2F& target, const float weight) const
	{
		return {
			Math::LerpF(x,  target.x, weight),
			Math::LerpF(y,  target.y, weight)
		};
	}

	//! Returns the value of this Vector2F with its length limited to a given max length.
	[[nodiscard]] constexpr Vector2F LimitLength(const float maxLength = 1.0f) const
	{
		const float lengthSquared = LengthSquared();

		if (const float maxLengthSquared = maxLength * maxLength; lengthSquared <= maxLengthSquared)
		{
			return *this;
		}

		const float scale = maxLength / Math::SqrtF(lengthSquared);

		return *this * scale;
	}

	//! Returns a Vector2F value where each component is the larger value between this Vector2F and another given Vector2F.
	[[nodiscard]] constexpr Vector2F Max(const Vector2F& other) const
	{
		return {
			Math::MaxF(x, other.x),
			Math::MaxF(y, other.y)
		};
	}

	//! Returns a Vector2F value where each component is the larger value between this Vector2F and a given float value.
	[[nodiscard]] constexpr Vector2F Max(const float value) const
	{
		return {
			Math::MaxF(x, value),
			Math::MaxF(y, value)
		};
	}

	//! Returns a Vector2F value where each component is the smaller value between this Vector2F and another given Vector2F.
	[[nodiscard]] constexpr Vector2F Min(const Vector2F& other) const
	{
		return {
			Math::MinF(x, other.x),
			Math::MinF(y, other.y)
		};
	}

	//! Returns a Vector2F value where each component is the smaller value between this Vector2F and a given float value.
	[[nodiscard]] constexpr Vector2F Min(const float value) const
	{
		return {
			Math::MinF(x, value),
			Math::MinF(y, value)
		};
	}

	//! Returns the point reached after moving this Vector2F toward another given Vector2F by up to a given delta distance.
	[[nodiscard]] constexpr Vector2F MoveToward(const Vector2F& other, const float delta) const
	{
		const Vector2F difference = other - *this;
		const float distance = difference.Length();

		if (distance <= delta || distance == 0.0f)
		{
			return other;
		}

		return *this + difference / distance * delta;
	}

	//! Returns the unit-length Vector2F in the same direction as this Vector2F.
	[[nodiscard]] constexpr Vector2F Normalized() const
	{
		const float length = Length();

		if (length <= 0.0f)
		{
			return Zero();
		}

		return *this / length;
	}

	//! Returns a Vector2F with each component in the range [0, mod] for its corresponding component of a given Vector2F mod value.
	[[nodiscard]] constexpr Vector2F PosMod(const Vector2F& mod) const
	{
		return {
			Math::PosModF(x, mod.x),
			Math::PosModF(y, mod.y)
		};
	}

	//! Returns a Vector2F with each component in the range [0, mod] for a given float mod value.
	[[nodiscard]] constexpr Vector2F PosMod(const float mod) const
	{
		return {
			Math::PosModF(x, mod),
			Math::PosModF(y, mod)
		};
	}

	//! Returns the Vector2F result of projecting this Vector2F onto another given Vector2F.
	[[nodiscard]] constexpr Vector2F Project(const Vector2F& other) const
	{
		const float denominator = other.LengthSquared();

		if (denominator == 0.0f)
		{
			return {};
		}

		return other * (Dot(other) / denominator);
	}

	//! Returns the reflected Vector2F result across a given surface normal Vector2F value.
	[[nodiscard]] constexpr Vector2F Reflect(const Vector2F& normal) const
	{
		return *this - normal * (2.0f * Dot(normal));
	}

	//! Returns the rotated Vector2F result around a given axis by a given angle.
	[[nodiscard]] constexpr Vector2F Rotated(const float angle) const
	{
		const float c = Math::CosF(angle);
		const float s = Math::SinF(angle);

		return {
			x * c - y * s,
			x * s + y * c
		};
	}

	//! Returns the Vector2F result of rounding this Vector2F's components to the nearest whole number (integer).
	[[nodiscard]] constexpr Vector2F Round() const
	{
		return {
			Math::RoundF(x),
			Math::RoundF(y)
		};
	}

	//! Returns -1 if a component is negative, 0 if zero, and +1 if positive for each component of this Vector2F.
	[[nodiscard]] constexpr Vector2F Sign() const
	{
		return {
			Math::SignF(x),
			Math::SignF(y)
		};
	}

	//! Returns the spherical interpolated Vector2F between this Vector and another given Vector2F at a given weight.
	[[nodiscard]] constexpr Vector2F Slerp(const Vector2F& other, const float weight) const
	{
		const float startLength = Length();
		const float endLength	 = other.Length();

		if (startLength == 0.0f || endLength == 0.0f)
		{
			return Lerp(other, weight);
		}

		const Vector2F start = *this / startLength;
		const Vector2F end	= other / endLength;

		const float dot   = Math::ClampF(start.Dot(end), -1.0f, 1.0f);
		const float angle = Math::AcosF(dot);

		if (Math::IsZeroApproxF(angle))
		{
			return Lerp(other, weight);
		}

		const float sine = Math::SinF(angle);
		const float startWeight = Math::SinF((1.0f - weight) * angle) / sine;
		const float endWeight	 = Math::SinF(weight * angle) / sine;

		const Vector2F direction = start * startWeight + end * endWeight;

		const float length = Math::LerpF(startLength, endLength, weight);

		return direction * length;
	}

	//! Returns the Vector2F result from sliding this Vector2F along a surface normal Vector2F value.
	[[nodiscard]] constexpr Vector2F Slide(const Vector2F& normal) const
	{
		return *this - normal * Dot(normal);
	}

	//! Returns the Vector2F result of snapping this Vector2F's components to the nearest corresponding step value.
	[[nodiscard]] constexpr Vector2F Snapped(const Vector2F& step) const
	{
		return {
			Math::SnappedF(x, step.x),
			Math::SnappedF(y, step.y)
		};
	}

	//! Returns the Vector2F result of snapping this Vector2F's components to the nearest step value.
	[[nodiscard]] constexpr Vector2F Snapped(const float step) const
	{
		return {
			Math::SnappedF(x, step),
			Math::SnappedF(y, step)
		};
	}

	// Comparison
	//! Returns whether or not this Vector2F approximately equals a given Vector2F based on a given epsilon value.
	[[nodiscard]] constexpr bool IsEqualApprox(const Vector2F& other, const float epsilon = 0.00001f) const
	{
		return	Math::IsEqualApproxF(x, other.x, epsilon) &&
				Math::IsEqualApproxF(y, other.y, epsilon);
	}

	//! Returns whether or not this Vector2F approximately equals zero based on a given epsilon value.
	[[nodiscard]] constexpr bool IsZeroApprox(const float epsilon = 0.00001f) const
	{
		return	Math::IsZeroApproxF(x, epsilon) &&
				Math::IsZeroApproxF(y, epsilon);
	}


	//============
	// Operators
	//============

	// Addition
	//! Adds each component of this Vector2F by each component of another given Vector2F.
	constexpr Vector2F operator+(const Vector2F& other) const
	{
		return {
			x + other.x,
			y + other.y
		};
	}

	//! Adds each component of this Vector2F by each component of another given Vector2F.
	constexpr Vector2F& operator+=(const Vector2F& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	// Subtraction
	//! Subtracts each component of this Vector2F by each component of another given Vector2F.
	constexpr Vector2F operator-(const Vector2F& other) const
	{
		return {
			x - other.x,
			y - other.y
		};
	}

	//! Subtracts each component of this Vector2F by each component of another given Vector2F.
	constexpr Vector2F& operator-=(const Vector2F& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	// Multiplication
	//! Multiplies each component of this Vector2F by each component of another given Vector2F.
	constexpr Vector2F operator*(const Vector2F& other) const
	{
		return {
			x * other.x,
			y * other.y
		};
	}

	//! Multiplies each component of this Vector2F by each component of another given Vector2F.
	constexpr Vector2F& operator*=(const Vector2F& other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	//! Multiplies each component of this Vector2F by a given scalar value.
	constexpr Vector2F operator*(const float scalar) const
	{
		return {
			x * scalar,
			y * scalar
		};
	}

	//! Multiplies each component of this Vector2F by a given scalar value.
	constexpr Vector2F& operator*=(const float scalar)
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}

	// Division
	//! Divides each component of this Vector2F by each component of another given Vector2F.
	constexpr Vector2F operator/(const Vector2F& other) const
	{
		return {
			x / other.x,
			y / other.y
		};
	}

	//! Divides each component of this Vector2F by each component of another given Vector2F.
	constexpr Vector2F& operator/=(const Vector2F& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	//! Divides each component of this Vector2F by a given scalar value.
	constexpr Vector2F operator/(const float scalar) const
	{
		return {
			x / scalar,
			y / scalar
		};
	}

	//! Divides each component of this Vector2F by a given scalar value.
	constexpr Vector2F& operator/=(const float scalar)
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}

	// Unary
	//! Returns the current value of this Vector2F.
	constexpr Vector2F operator+() const
	{
		return *this;
	}

	//! Returns the negative value of this Vector2F.
	constexpr Vector2F operator-() const
	{
		return {-x, -y};
	}

	// Comparison
	//! Returns whether or not this Vector2F is less than a given right Vector2F in order of x, y, z.
	constexpr bool operator<(const Vector2F& right) const
	{
		if (x != right.x)
		{
			return x < right.x;
		}

		return y < right.y;
	}

	//! Returns whether or not this Vector2F is less than or equal to a given right Vector2F in order of x, y, z.
	constexpr bool operator<=(const Vector2F& right) const
	{
		if (x != right.x)
		{
			return x <= right.x;
		}

		return y <= right.y;
	}

	//! Returns whether or not this Vector2F is greater than a given right Vector2F in order of x, y, z.
	constexpr bool operator>(const Vector2F& right) const
	{
		if (x != right.x)
		{
			return x > right.x;
		}

		return y > right.y;
	}

	//! Returns whether or not this Vector2F is greater than or equal to a given right Vector2F in order of x, y, z.
	constexpr bool operator>=(const Vector2F& right) const
	{
		if (x != right.x)
		{
			return x >= right.x;
		}

		return y >= right.y;
	}

	//! Returns whether or not this Vector2F is equal to a given right Vector2F.
	constexpr bool operator==(const Vector2F& right) const
	{
		return x == right.x && y == right.y;
	}

	//! Returns whether or not this Vector2F is not equal to a given right Vector2F.
	constexpr bool operator!=(const Vector2F& right) const
	{
		return !(*this == right);
	}
};