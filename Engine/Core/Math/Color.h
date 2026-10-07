//===================================================
// Color.h
// Author: Moca 9/10/2026
// Defines a linear Color type to be used
// as the basis for color calculation.
//===================================================
#pragma once

//! Linear color type used as the basis for all color calculations. -Moca
struct Color
{
	float r = 0.0f;	//! Red color value
	float g = 0.0f;	//! Green color value
	float b = 0.0f; //! Blue color value
	float a = 0.0f; //! Alpha value


	//=================
	// Static Presets
	//=================

	//! Returns a black Color value.
	static constexpr Color Black()
	{
		return {.r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f};
	}

	//! Returns a white Color value.
	static constexpr Color White()
	{
		return {.r = 1.0f, .g = 1.0f, .b = 1.0f, .a = 1.0f};
	}

	//! Returns a transparent Color value.
	static constexpr Color Transparent()
	{
		return {.r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 0.0f};
	}


	//=============
	// Conversion
	//=============
	//
	//! Converts a hex color value into RGBA float format.
	static constexpr Color FromHex(const uint32 hexValue)
	{
		return {
			.r = ((hexValue >> 16) & 0xFF) / 255.0f,
			.g = ((hexValue >> 8) & 0xFF) / 255.0f,
			.b = (hexValue & 0xFF) / 255.0f,
			.a = ((hexValue >> 24) & 0xFF) / 255.0f
		};
	}


	//============
	// Operators
	//============

	constexpr Color& operator=(const Color& other) = default;

	constexpr Color& operator=(const uint32 hexValue)
	{
		*this = FromHex(hexValue);
		return *this;
	}

	constexpr Color operator+(const Color& other) const
	{
		return {
			.r = r + other.r,
			.g = g + other.g,
			.b = b + other.b,
			.a = a + other.a,
		};
	}

	constexpr Color& operator+=(const Color& other)
	{
		r += other.r;
		g += other.g;
		b += other.b;
		a += other.a;

		return *this;
	}

	constexpr Color operator-(const Color& other) const
	{
		return {
			.r = r - other.r,
			.g = g - other.g,
			.b = b - other.b,
			.a = a - other.a
		};
	}

	constexpr Color& operator-=(const Color& other)
	{
		r -= other.r;
		g -= other.g;
		b -= other.b;
		a -= other.a;

		return *this;
	}

	constexpr Color operator*(const Color& other) const
	{
		return {
			.r = r * other.r,
			.g = g * other.g,
			.b = b * other.b,
			.a = a * other.a
		};
	}

	constexpr Color& operator*=(const Color& other)
	{
		r *= other.r;
		g *= other.g;
		b *= other.b;
		a *= other.a;

		return *this;
	}

	constexpr Color operator/(const Color& other) const
	{
		return {
			.r = r / other.r,
			.g = g / other.g,
			.b = b / other.b,
			.a = a / other.a
		};
	}

	constexpr Color& operator/=(const Color& other)
	{
		r /= other.r;
		g /= other.g;
		b /= other.b;
		a /= other.a;

		return *this;
	}

	// Scalar

	constexpr Color operator*(const float scalar) const
	{
		return {
			.r = r * scalar,
			.g = g * scalar,
			.b = b * scalar,
			.a = a * scalar
		};
	}

	constexpr Color& operator*=(const float scalar)
	{
		r *= scalar;
		g *= scalar;
		b *= scalar;
		a *= scalar;

		return *this;
	}

	constexpr Color operator/(const float scalar) const
	{
		return {
			.r = r / scalar,
			.g = g / scalar,
			.b = b / scalar,
			.a = a / scalar
		};
	}

	constexpr Color& operator/=(const float scalar)
	{
		r /= scalar;
		g /= scalar;
		b /= scalar;
		a /= scalar;

		return *this;
	}

	// Comparison

	constexpr bool operator==(const Color& right) const
	{
		return r == right.r && g == right.g && b == right.b && a == right.a;
	}

	constexpr bool operator!=(const Color& right) const
	{
		return !(*this == right);
	}
};