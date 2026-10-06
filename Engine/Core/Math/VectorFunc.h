#pragma once

#include "Vector3.h"
#include "Vector3F.h"
#include "Quaternion.h"
#include "QuaternionF.h"

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

	constexpr Quaternion ToDoubleQuat(const QuaternionF& value)
	{
		return {
			static_cast<double>(value.q.w),
			static_cast<double>(value.q.x),
			static_cast<double>(value.q.y),
			static_cast<double>(value.q.z)
		};
	}

	constexpr QuaternionF ToFloatQuat(const Quaternion& value)
	{
		return {
			static_cast<float>(value.q.w),
			static_cast<float>(value.q.x),
			static_cast<float>(value.q.y),
			static_cast<float>(value.q.z)
		};
	}
}