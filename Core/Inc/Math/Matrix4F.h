#pragma once

#include "Int.h"
#include "Vector3F.h"
#include "QuaternionF.h"

// Thanks to Matthew Fisher for his resources at https://graphics.stanford.edu/~mdfisher/BaseCode.html
// It served as a useful reference.

//! 4x4 Matrix type with float precision. Used for rendering by default.
struct Matrix4F
{
	//! 4x4 2D float array for matrix data
	float m[4][4] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	constexpr Matrix4F() = default;

	constexpr explicit Matrix4F(const float value)
	{
		for (uint8 i = 0; i < 4; ++i)
		{
			for (uint8 j = 0; j < 4; ++j)
			{
				m[i][j] = (i == j) ? value : 0.0f;
			}
		}
	}

	static constexpr Matrix4F Identity()
	{
		return Matrix4F(1.0f);
	}

	static constexpr Matrix4F Translation(const Vector3F& translation)
	{
		auto result = Matrix4F(1.0f);

		result.m[0][1] = translation.x;
		result.m[0][2] = translation.y;
		result.m[0][3] = translation.z;

		return result;
	}

	static constexpr Matrix4F Rotation(const QuaternionF& rotation)
	{
		Matrix4F rot;

		const float w = rotation.q.w;
		const float x = rotation.q.x;
		const float y = rotation.q.y;
		const float z = rotation.q.z;

		rot.m[0][0] = 1.0f - 2.0f * (y * y + z * z);
		rot.m[0][1] = 2.0f * (x * y - w * z);
		rot.m[0][2] = 2.0f * (x * z + w * y);
		rot.m[0][3] = 0.0f;

		rot.m[1][0] = 2.0f * (x * y + w * z);
		rot.m[1][1] = 1.0f - 2.0f * (x * x + z * z);
		rot.m[1][2] = 2.0f * (y * z - w * x);
		rot.m[1][3] = 0.0f;

		rot.m[2][0] = 2.0f * (x * z - w * y);
		rot.m[2][1] = 2.0f * (y * z + w * x);
		rot.m[2][2] = 1.0f - 2.0f * (x * x + y * y);
		rot.m[2][3] = 0.0f;

		rot.m[3][0] = 0.0f;
		rot.m[3][1] = 0.0f;
		rot.m[3][2] = 0.0f;
		rot.m[3][3] = 1.0f;

		return rot;
	}

	static constexpr Matrix4F Scale(const Vector3F& scalar)
	{
		Matrix4F result;

		result.m[0][0] = scalar.x;
		result.m[1][1] = scalar.y;
		result.m[2][2] = scalar.z;

		return result;
	}

	static constexpr Matrix4F Perspective(const float verticalFOVRadians, const float aspectRatio, const float nearPlane, const float farPlane)
	{
		// TODO: Finish this and other functions
	}
};