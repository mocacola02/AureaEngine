//===================================================
// MathFunc.h
// Author: Moca 9/10/2026
// Defines a Math namespace used for
// various math helpers.
//===================================================
#pragma once

#include <cmath>

//! Namespace used for various math helpers, primarily focusing on float and double types. -Moca
namespace Math
{
	//========
	// int32
	//========

	constexpr int32 AbsI(const int32 value)
	{
		return value < 0 ? -value : value;
	}

	constexpr int32 ClampI(const int32 value, const int32 min, const int32 max)
	{
		return value < min ? min : value > max ? max : value;
	}

	constexpr int32 MaxI(const int32 a, const int32 b)
	{
		return a > b ? a : b;
	}

	constexpr int32 MinI(const int32 a, const int32 b)
	{
		return a < b ? a : b;
	}

	constexpr int32 SignI(const int32 value)
	{
		return value > 0 ? 1 : value < 0 ? -1 : 0;
	}

	constexpr bool IsFiniteI(const int32 value)
	{
		return isfinite(value);
	}


	//========
	// uint32
	//========

	constexpr uint32 AbsU(const uint32 value)
	{
		return value < 0 ? -value : value;
	}

	constexpr uint32 ClampU(const uint32 value, const uint32 min, const uint32 max)
	{
		return value < min ? min : value > max ? max : value;
	}

	constexpr uint32 MaxU(const uint32 a, const uint32 b)
	{
		return a > b ? a : b;
	}

	constexpr uint32 MinU(const uint32 a, const uint32 b)
	{
		return a < b ? a : b;
	}

	constexpr uint32 SignU(const uint32 value)
	{
		return value > 0 ? 1 : value < 0 ? -1 : 0;
	}

	constexpr bool IsFiniteU(const uint32 value)
	{
		return isfinite(value);
	}



	//========
	// Float
	//========

	// General
	constexpr float AbsF(const float value)
	{
		return value < 0.0f ? -value : value;
	}

	constexpr float AcosF(const float value)
	{
		return acosf(value);
	}

	constexpr float AsinF(const float value)
	{
		return asinf(value);
	}

	constexpr float Atan2F(const float a, const float b)
	{
		return atan2f(a, b);
	}

	constexpr float CeilF(const float value)
	{
		return ceilf(value);
	}

	constexpr float ClampF(const float value, const float min, const float max)
	{
		return value < min ? min : value > max ? max : value;
	}

	constexpr float FloorF(const float value)
	{
		return floorf(value);
	}

	constexpr float SqrtF(const float value)
	{
		return sqrtf(value);
	}

	constexpr float SinF(const float value)
	{
		return sinf(value);
	}

	constexpr float CosF(const float value)
	{
		return cosf(value);
	}

	constexpr float LerpF(const float a, const float b, const float weight)
	{
		return a + (b - a) * weight;
	}

	constexpr float MaxF(const float a, const float b)
	{
		return a > b ? a : b;
	}

	constexpr float MinF(const float a, const float b)
	{
		return a < b ? a : b;
	}

	constexpr float PosModF(const float value, const float mod)
	{
		float result = fmodf(value, mod);

		if (result < 0.0f)
		{
			result += mod;
		}

		return result;
	}

	constexpr float RoundF(const float value)
	{
		return roundf(value);
	}

	constexpr float SignF(const float value)
	{
		return value > 0.0f ? 1.0f : value < 0.0f ? -1.0f : 0.0f;
	}

	constexpr float SnappedF(const float value, const float step)
	{
		if (step == 0.0f)
		{
			return value;
		}

		return RoundF(value / step) * step;
	}

	constexpr float TanF(const float value)
	{
		return tanf(value);
	}

	// Rotation
	constexpr float PiF  = 3.14159265358979f;
	constexpr float TauF = 6.28318530717959f;

	constexpr float DegreesToRadiansF(const float degrees)
	{
		return degrees * (PiF / 180.0f);
	}

	constexpr float RadiansToDegreesF(const float radians)
	{
		return radians * (180.0f / PiF);
	}

	// Comparison
	constexpr bool IsEqualApproxF(const float a, const float b, const float epsilon = 0.00001f)
	{
		return AbsF(a - b) <= epsilon;
	}

	constexpr bool IsZeroApproxF(const float value, const float epsilon = 0.00001f)
	{
		return AbsF(value) <= epsilon;
	}

	constexpr bool IsFiniteF(const float value)
	{
		return isfinite(value);
	}


	//=========
	// Double
	//=========

	// General
	constexpr double Abs(const double value)
	{
		return value < 0.0 ? -value : value;
	}

	constexpr double Acos(const double value)
	{
		return acos(value);
	}

	constexpr double Asin(const double value)
	{
		return asin(value);
	}

	constexpr double Atan2(const double a, const double b)
	{
		return atan2(a, b);
	}

	constexpr double Ceil(const double value)
	{
		return ceil(value);
	}

	constexpr double Clamp(const double value, const double min, const double max)
	{
		return value < min ? min : value > max ? max : value;
	}

	constexpr double Floor(const double value)
	{
		return floor(value);
	}

	constexpr double Sqrt(const double value)
	{
		return sqrt(value);
	}

	constexpr double Sin(const double value)
	{
		return sin(value);
	}

	constexpr double Cos(const double value)
	{
		return cos(value);
	}

	constexpr double Lerp(const double a, const double b, const double weight)
	{
		return a + (b - a) * weight;
	}

	constexpr double Max(const double a, const double b)
	{
		return a > b ? a : b;
	}

	constexpr double Min(const double a, const double b)
	{
		return a < b ? a : b;
	}

	constexpr double PosMod(const double value, const double mod)
	{
		double result = fmod(value, mod);

		if (result < 0.0)
		{
			result += mod;
		}

		return result;
	}

	constexpr double Round(const double value)
	{
		return round(value);
	}

	constexpr double Sign(const double value)
	{
		return value > 0.0 ? 1.0 : value < 0.0 ? -1.0 : 0.0;
	}

	constexpr double Snapped(const double value, const double step)
	{
		if (step == 0.0)
		{
			return value;
		}

		return Round(value / step) * step;
	}

	constexpr double Tan(const double value)
	{
		return tan(value);
	}

	// Rotation
	constexpr double Pi  = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;
	constexpr double Tau = 6.2831853071795864769252867665590057683943387987502116419498891846156328124;

	constexpr double DegreesToRadians(const double degrees)
	{
		return degrees * (Pi / 180.0);
	}

	constexpr double RadiansToDegrees(const double radians)
	{
		return radians * (180.0 / Pi);
	}

	// Comparison
	//! Returns whether or not a and b are approximately equal based on a given epsilon.
	constexpr bool IsEqualApprox(const double a, const double b, const double epsilon = 0.00001)
	{
		return Abs(a - b) <= epsilon;
	}

	//! Returns whether or not a is approximately greater than b based on a given epsilon.
	constexpr bool IsGreaterThanApprox(const double a, const double b, const double epsilon = 0.00001)
	{
		return a >= b + epsilon;
	}

	//! Returns whether or not a is approximately greater than or equal to b based on a given epsilon.
	constexpr bool IsGreaterThanOrEqualApprox(const double a, const double b, const double epsilon = 0.00001)
	{
		return a >= b - epsilon;
	}

	//! Returns whether or not a is approximately less than b based on a given epsilon.
	constexpr bool IsLessThanApprox(const double a, const double b, const double epsilon = 0.00001)
	{
		return a <= b - epsilon;
	}

	//! Returns whether or not a is approximately less than or equal to b based on a given epsilon.
	constexpr bool IsLessThanOrEqualApprox(const double a, const double b, const double epsilon = 0.00001)
	{
		return a <= b + epsilon;
	}

	//! Returns whether or not a given value is approximately equal to zero based on a given epsilon.
	constexpr bool IsZeroApprox(const double value, const double epsilon = 0.00001)
	{
		return Abs(value) <= epsilon;
	}

	constexpr bool IsFinite(const double value)
	{
		return isfinite(value);
	}
}