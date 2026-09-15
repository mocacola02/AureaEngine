#pragma once

#include "Color.h"
#include "Int.h"
#include "MathFunc.h"
#include "Matrix4F.h"
#include "QuaternionF.h"
#include "Vector3.h"
#include "Vector3F.h"
#include "Vector4.h"
#include "Vector4F.h"

namespace Math
{
	constexpr Vector3 ToDoubleVector3(const Vector3F& value)
	{
		return {
			static_cast<double>(value.x),
			static_cast<double>(value.y),
			static_cast<double>(value.z)
		};
	}

	constexpr Vector3F ToFloatVector3(const Vector3& value)
	{
		return {
			static_cast<float>(value.x),
			static_cast<float>(value.y),
			static_cast<float>(value.z)
		};
	}
}