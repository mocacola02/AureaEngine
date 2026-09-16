//===================================================
// Matrix4F.h
// Author: Moca 9/16/2026
// Defines a 4x4 Matrix type with float precision.
//===================================================
#pragma once

#include "Int.h"
#include "VectorFunc.h"

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

	//! Default Matrix4F constructor
	constexpr Matrix4F() = default;

	//! Matrix4F constructor from float
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

	//! Returns a Matrix4F constructed using 1.0f.
	//! Same Matrix4F result as the default constructor.
	static constexpr Matrix4F Identity()
	{
		return Matrix4F(1.0f);
	}


	//===================
	// Static Functions
	//===================

	//! Converts a given Vector3F translation value into a Matrix4F.
	static constexpr Matrix4F Translation(const Vector3F& translation)
	{
		auto result = Matrix4F(1.0f);

		result.m[0][1] = translation.x;
		result.m[0][2] = translation.y;
		result.m[0][3] = translation.z;

		return result;
	}

	//! Converts a given Vector3 translation value into a Matrix4F.
	static constexpr Matrix4F Translation(const Vector3& translation)
	{
		return Translation(Math::ToFloatVector3(translation));
	}

	//! Converts a given QuaternionF rotation value into a Matrix4F.
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

	//! Converts a given Quaternion rotation value into a Matrix4F.
	static constexpr Matrix4F Rotation(const Quaternion& rotation)
	{
		return Rotation(Math::ToFloatQuat(rotation));
	}

	//! Converts a given Vector3F scalar value into a Matrix4F.
	static constexpr Matrix4F Scale(const Vector3F& scalar)
	{
		Matrix4F result;

		result.m[0][0] = scalar.x;
		result.m[1][1] = scalar.y;
		result.m[2][2] = scalar.z;

		return result;
	}

	//! Converts a given Vector3F scalar value into a Matrix4F.
	static constexpr Matrix4F Scale(const Vector3& scalar)
	{
		return Scale(Math::ToFloatVector3(scalar));
	}

	//! Inverts a given Matrix4F.
	static constexpr Matrix4F Inverse(const Matrix4F& m)
	{
		float a[4][8];

		for (uint8 i = 0; i < 4; ++i)
		{
			for (uint8 j = 0; j < 4; ++j)
			{
				a[i][j] = m.m[i][j];
			}

			for (uint8 j = 0; j < 4; ++j)
			{
				a[i][j + 4] = (j == i ? 1.0f : 0.0f);
			}
		}

		for (uint8 col = 0; col < 4; ++col)
		{
			uint8 pivot = col;
			float maxAbs = Math::AbsF(a[col][col]);

			for (uint8 i = col + 1; i < 4; ++i)
			{
				if (Math::AbsF(a[i][col]) > maxAbs)
				{
					maxAbs = Math::AbsF(a[i][col]);
					pivot = i;
				}
			}

			if (pivot != col && maxAbs < 1e-12f)
			{
				return Matrix4F(0.0f);
			}

			if (pivot != col)
			{
				for (uint8 j = col; j < 8; ++j)
				{
					const float tmp = a[col][j];
					a[col][j] = a[pivot][j];
					a[pivot][j] = tmp;
				}
			}

			const float pivotVal = a[col][col];

			for (uint8 j = col; j < 8; ++j)
			{
				a[col][j] /= pivotVal;
			}

			for (uint8 i = 0; i < 4; ++i)
			{
				if (i == col)
				{
					continue;
				}

				const float factor = a[i][col];

				if (Math::AbsF(factor) > 1e-12f)
				{
					for (uint8 j = col; j < 8; ++j)
					{
						a[i][j] -= factor * a[col][j];
					}
				}
			}
		}

		Matrix4F inv;

		for (uint8 i = 0; i < 4; ++i)
		{
			for (uint8 j = 0; j < 4; ++j)
			{
				inv.m[i][j] = a[i][j + 4];
			}
		}

		return inv;
	}

	//! Calculates a perspective Matrix4F based on a given FOV, aspect ratio, near plane, and far plane.
	static constexpr Matrix4F Perspective(const float verticalFOVRadians, const float aspectRatio, const float nearPlane, const float farPlane)
	{
		const float width  = 1.0f / Math::TanF(verticalFOVRadians * 0.5f);
		const float invNearMinusFar = 1.0f / (nearPlane - farPlane);

		Matrix4F result;

		result.m[0][0] = width / aspectRatio;

		result.m[1][1] = width;

		result.m[2][2] = (nearPlane + farPlane) * invNearMinusFar;
		result.m[2][3] = (farPlane * nearPlane - farPlane * aspectRatio) * invNearMinusFar;

		result.m[3][2] = -(nearPlane + farPlane) * invNearMinusFar;
		result.m[3][3] = 0.0f;

		return result;
	}

	//! Calculates a Matrix4F looking at a target using a given eye, target, and up Vector3F.
	static constexpr Matrix4F LookAt(const Vector3F& eye, const Vector3F& target, const Vector3F& up)
	{
		if (eye == target)
		{
			return Identity();
		}

		// CONSIDER: The function calls for Vector3(F) in this situation are kinda clunky, add static versions to MathFunc?
		const Vector3F zAxis = (eye - target).Normalized();
		const Vector3F xAxis = up.Cross(zAxis).Normalized();
		const Vector3F yAxis = zAxis.Cross(xAxis).Normalized();

		Matrix4F result;

		result.m[0][0] =  xAxis.x;
		result.m[0][1] =  xAxis.y;
		result.m[0][2] =  xAxis.z;
		result.m[0][3] = -xAxis.Dot(eye);

		result.m[1][0] =  yAxis.x;
		result.m[1][1] =  yAxis.y;
		result.m[1][2] =  yAxis.z;
		result.m[1][3] = -yAxis.Dot(eye);

		result.m[2][0] =  zAxis.x;
		result.m[2][1] =  zAxis.y;
		result.m[2][2] =  zAxis.z;
		result.m[2][3] = -zAxis.Dot(eye);

		return result;
	}


	//===============
	// Modification
	//===============

	//! Transposes this Matrix4F.
	[[nodiscard]] constexpr Matrix4F Transpose() const
	{
		Matrix4F result;

		for (uint8 i = 0; i < 4; ++i)
		{
			for (uint8 j = 0; j < 4; ++j)
			{
				result.m[j][i] = m[i][j];
			}
		}

		return result;
	}


	//===============
	// Misc Helpers
	//===============

	//! Returns whether or not this Matrix4F approximately equals another given Matrix4F.
	[[nodiscard]] constexpr bool IsEqualApprox(const Matrix4F& other, const float epsilon = 0.00001f) const
	{
		for (uint8 i = 0; i < 4; ++i)
		{
			for (uint8 j = 0; j < 4; ++j)
			{
				if (Math::AbsF(m[i][j] - other.m[i][j]) > epsilon)
				{
					return false;
				}
			}
		}

		return true;
	}


	//================
	// Data fetching
	//================

	//! Returns a pointer to the float data of this Matrix4F.
	constexpr float* Data()
	{
		return *m;
	}

	//! Returns a constant pointer to the float data of this Matrix4F.
	[[nodiscard]] constexpr const float* Data() const
	{
		return *m;
	}


	//============
	// Operators
	//============

	// Addition
	//! Adds the values of this Matrix4F by another given Matrix4F.
	constexpr Matrix4F operator+(const Matrix4F& other) const
	{
		Matrix4F result;

		for (uint8 i = 0; i < 4; ++i)
		{
			for (uint8 j = 0; j < 4; ++j)
			{
				result.m[i][j] = m[i][j] + other.m[i][j];
			}
		}

		return result;
	}

	//! Adds the values of this Matrix4F by another given Matrix4F.
	constexpr Matrix4F operator+=(const Matrix4F& other) const
	{
		return *this + other;
	}

	// Subtraction
	//! Subtracts the values of this Matrix4F by another given Matrix4F.
	constexpr Matrix4F operator-(const Matrix4F& other) const
	{
		Matrix4F result;

		for (uint8 i = 0; i < 4; ++i)
		{
			for (uint8 j = 0; j < 4; ++j)
			{
				result.m[i][j] = m[i][j] - other.m[i][j];
			}
		}

		return result;
	}

	//! Subtracts the values of this Matrix4F by another given Matrix4F.
	constexpr Matrix4F operator-=(const Matrix4F& other) const
	{
		return *this - other;
	}

	// Multiplication
	//! Multiplies the values of this Matrix4F by another given Matrix4F.
	constexpr Matrix4F operator*(const Matrix4F& other) const
	{
		Matrix4F result;

		for (uint8 i = 0; i < 4; ++i)
		{
			for (uint8 j = 0; j < 4; ++j)
			{
				float total = 0.0f;

				for (uint8 k = 0; k < 4; ++k)
				{
					total += m[i][k] * other.m[k][j];
				}

				result.m[i][j] = total;
			}
		}

		return result;
	}

	//! Multiplies the values of this Matrix4F by a given float.
	constexpr Matrix4F operator*(const float other) const
	{
		Matrix4F result;

		for (uint8 i = 0; i < 4; ++i)
		{
			for (uint8 j = 0; j < 4; ++j)
			{
				result.m[i][j] = m[i][j] * other;
			}
		}

		return result;
	}

	//! Multiplies the values of this Matrix4F by another given Matrix4F.
	constexpr Matrix4F operator*=(const Matrix4F& other) const
	{
		return *this * other;
	}

	//! Multiplies the values of this Matrix4F by a given float.
	constexpr Matrix4F operator*=(const float other) const
	{
		return *this * other;
	}

	// Comparison
	//! Returns whether or not this Matrix4F is approximately equal to another given Matrix4F.
	//! IsEqualApprox() is used here to avoid potential precision errors.
	constexpr bool operator==(const Matrix4F& other) const
	{
		return IsEqualApprox(other);
	}

	//! Returns whether or not this Matrix4F is not approximately equal to another given Matrix4F.
	//! !IsEqualApprox() is used here to avoid potential precision errors.
	constexpr bool operator!=(const Matrix4F& other) const
	{
		return !IsEqualApprox(other);
	}
};