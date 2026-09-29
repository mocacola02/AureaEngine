//===================================================
// Matrix4.h
// Author: Moca 9/16/2026
// Defines a 4x4 Matrix type with double precision.
//===================================================
#pragma once

#include "Int.h"
#include "VectorFunc.h"

// Thanks to Matthew Fisher for his resources at https://graphics.stanford.edu/~mdfisher/BaseCode.html
// It served as a useful reference.

//! 4x4 Matrix type with double precision.
struct Matrix4
{
	//! 4x4 2D double array for matrix data
	double m[4][4] = {
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};

	//! Default Matrix4 constructor
	constexpr Matrix4() = default;

	//! Matrix4 constructor from double
	constexpr explicit Matrix4(const double value)
	{
		for (uint8 i = 0; i < 4; ++i)
		{
			for (uint8 j = 0; j < 4; ++j)
			{
				m[i][j] = i == j ? value : 0.0;
			}
		}
	}

	//! Returns a Matrix4 constructed using 1.0f.
	//! Same Matrix4 result as the default constructor.
	static constexpr Matrix4 Identity()
	{
		return Matrix4(1.0);
	}


	//===================
	// Static Functions
	//===================

	//! Converts a given Vector3F translation value into a Matrix4.
	static constexpr Matrix4 Translation(const Vector3& translation)
	{
		auto result = Matrix4(1.0);

		result.m[0][1] = translation.x;
		result.m[0][2] = translation.y;
		result.m[0][3] = translation.z;

		return result;
	}

	//! Converts a given Vector3 translation value into a Matrix4.
	static constexpr Matrix4 Translation(const Vector3F& translation)
	{
		return Translation(Math::ToDoubleVector3(translation));
	}

	//! Converts a given QuaternionF rotation value into a Matrix4.
	static constexpr Matrix4 Rotation(const Quaternion& rotation)
	{
		Matrix4 rot;

		const double w = rotation.q.w;
		const double x = rotation.q.x;
		const double y = rotation.q.y;
		const double z = rotation.q.z;

		rot.m[0][0] = 1.0 - 2.0 * (y * y + z * z);
		rot.m[0][1] = 2.0 * (x * y - w * z);
		rot.m[0][2] = 2.0 * (x * z + w * y);
		rot.m[0][3] = 0.0;

		rot.m[1][0] = 2.0 * (x * y + w * z);
		rot.m[1][1] = 1.0 - 2.0 * (x * x + z * z);
		rot.m[1][2] = 2.0 * (y * z - w * x);
		rot.m[1][3] = 0.0;

		rot.m[2][0] = 2.0 * (x * z - w * y);
		rot.m[2][1] = 2.0 * (y * z + w * x);
		rot.m[2][2] = 1.0 - 2.0 * (x * x + y * y);
		rot.m[2][3] = 0.0;

		rot.m[3][0] = 0.0;
		rot.m[3][1] = 0.0;
		rot.m[3][2] = 0.0;
		rot.m[3][3] = 1.0;

		return rot;
	}

	//! Converts a given Quaternion rotation value into a Matrix4.
	static constexpr Matrix4 Rotation(const QuaternionF& rotation)
	{
		return Rotation(Math::ToDoubleQuat(rotation));
	}

	//! Converts a given Vector3F scalar value into a Matrix4.
	static constexpr Matrix4 Scale(const Vector3& scalar)
	{
		Matrix4 result;

		result.m[0][0] = scalar.x;
		result.m[1][1] = scalar.y;
		result.m[2][2] = scalar.z;

		return result;
	}

	//! Converts a given Vector3F scalar value into a Matrix4.
	static constexpr Matrix4 Scale(const Vector3F& scalar)
	{
		return Scale(Math::ToDoubleVector3(scalar));
	}

	//! Inverts a given Matrix4.
	static constexpr Matrix4 Inverse(const Matrix4& m)
	{
		double a[4][8];

		for (uint8 i = 0; i < 4; ++i)
		{
			for (uint8 j = 0; j < 4; ++j)
			{
				a[i][j] = m.m[i][j];
			}

			for (uint8 j = 0; j < 4; ++j)
			{
				a[i][j + 4] = j == i ? 1.0 : 0.0;
			}
		}

		for (uint8 col = 0; col < 4; ++col)
		{
			uint8 pivot = col;
			double maxAbs = Math::Abs(a[col][col]);

			for (uint8 i = col + 1; i < 4; ++i)
			{
				if (Math::Abs(a[i][col]) > maxAbs)
				{
					maxAbs = Math::Abs(a[i][col]);
					pivot = i;
				}
			}

			if (pivot != col && maxAbs < 1e-12)
			{
				return Matrix4(0.0);
			}

			if (pivot != col)
			{
				for (uint8 j = col; j < 8; ++j)
				{
					const double tmp = a[col][j];
					a[col][j] = a[pivot][j];
					a[pivot][j] = tmp;
				}
			}

			const double pivotVal = a[col][col];

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

				if (const double factor = a[i][col]; Math::Abs(factor) > 1e-12)
				{
					for (uint8 j = col; j < 8; ++j)
					{
						a[i][j] -= factor * a[col][j];
					}
				}
			}
		}

		Matrix4 inv;

		for (uint8 i = 0; i < 4; ++i)
		{
			for (uint8 j = 0; j < 4; ++j)
			{
				inv.m[i][j] = a[i][j + 4];
			}
		}

		return inv;
	}

	//! Calculates a perspective Matrix4 based on a given FOV, aspect ratio, near plane, and far plane.
	static constexpr Matrix4 Perspective(const double verticalFOVRadians, const double aspectRatio, const double nearPlane, const double farPlane)
	{
		const double width  = 1.0 / Math::Tan(verticalFOVRadians * 0.5);
		const double invNearMinusFar = 1.0 / (nearPlane - farPlane);

		Matrix4 result;

		result.m[0][0] = width / aspectRatio;

		result.m[1][1] = width;

		result.m[2][2] = (nearPlane + farPlane) * invNearMinusFar;
		result.m[2][3] = (farPlane * nearPlane - farPlane * aspectRatio) * invNearMinusFar;

		result.m[3][2] = -(nearPlane + farPlane) * invNearMinusFar;
		result.m[3][3] = 0.0;

		return result;
	}

	//! Calculates a Matrix4 looking at a target using a given eye, target, and up Vector3F.
	static constexpr Matrix4 LookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
	{
		if (eye == target)
		{
			return Identity();
		}

		// CONSIDER: The function calls for Vector3(F) in this situation are kinda clunky, add static versions to MathFunc?
		const Vector3 zAxis = (eye - target).Normalized();
		const Vector3 xAxis = up.Cross(zAxis).Normalized();
		const Vector3 yAxis = zAxis.Cross(xAxis).Normalized();

		Matrix4 result;

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

	//! Transposes this Matrix4.
	[[nodiscard]] constexpr Matrix4 Transpose() const
	{
		Matrix4 result;

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

	//! Returns whether or not this Matrix4 approximately equals another given Matrix4.
	[[nodiscard]] constexpr bool IsEqualApprox(const Matrix4& other, const double epsilon = 0.00001) const
	{
		for (uint8 i = 0; i < 4; ++i)
		{
			for (uint8 j = 0; j < 4; ++j)
			{
				if (Math::Abs(m[i][j] - other.m[i][j]) > epsilon)
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

	//! Returns a pointer to the double data of this Matrix4.
	constexpr double* Data()
	{
		return *m;
	}

	//! Returns a constant pointer to the double data of this Matrix4.
	[[nodiscard]] constexpr const double* Data() const
	{
		return *m;
	}


	//============
	// Operators
	//============

	// Addition
	//! Adds the values of this Matrix4 by another given Matrix4.
	constexpr Matrix4 operator+(const Matrix4& other) const
	{
		Matrix4 result;

		for (uint8 i = 0; i < 4; ++i)
		{
			for (uint8 j = 0; j < 4; ++j)
			{
				result.m[i][j] = m[i][j] + other.m[i][j];
			}
		}

		return result;
	}

	//! Adds the values of this Matrix4 by another given Matrix4.
	constexpr Matrix4 operator+=(const Matrix4& other) const
	{
		return *this + other;
	}

	// Subtraction
	//! Subtracts the values of this Matrix4 by another given Matrix4.
	constexpr Matrix4 operator-(const Matrix4& other) const
	{
		Matrix4 result;

		for (uint8 i = 0; i < 4; ++i)
		{
			for (uint8 j = 0; j < 4; ++j)
			{
				result.m[i][j] = m[i][j] - other.m[i][j];
			}
		}

		return result;
	}

	//! Subtracts the values of this Matrix4 by another given Matrix4.
	constexpr Matrix4 operator-=(const Matrix4& other) const
	{
		return *this - other;
	}

	// Multiplication
	//! Multiplies the values of this Matrix4 by another given Matrix4.
	constexpr Matrix4 operator*(const Matrix4& other) const
	{
		Matrix4 result;

		for (uint8 i = 0; i < 4; ++i)
		{
			for (uint8 j = 0; j < 4; ++j)
			{
				double total = 0.0f;

				for (uint8 k = 0; k < 4; ++k)
				{
					total += m[i][k] * other.m[k][j];
				}

				result.m[i][j] = total;
			}
		}

		return result;
	}

	//! Multiplies the values of this Matrix4 by a given double.
	constexpr Matrix4 operator*(const double other) const
	{
		Matrix4 result;

		for (uint8 i = 0; i < 4; ++i)
		{
			for (uint8 j = 0; j < 4; ++j)
			{
				result.m[i][j] = m[i][j] * other;
			}
		}

		return result;
	}

	//! Multiplies the values of this Matrix4 by another given Matrix4.
	constexpr Matrix4 operator*=(const Matrix4& other) const
	{
		return *this * other;
	}

	//! Multiplies the values of this Matrix4 by a given double.
	constexpr Matrix4 operator*=(const double other) const
	{
		return *this * other;
	}

	// Comparison
	//! Returns whether or not this Matrix4 is approximately equal to another given Matrix4.
	//! IsEqualApprox() is used here to avoid potential precision errors.
	constexpr bool operator==(const Matrix4& other) const
	{
		return IsEqualApprox(other);
	}

	//! Returns whether or not this Matrix4 is not approximately equal to another given Matrix4.
	//! !IsEqualApprox() is used here to avoid potential precision errors.
	constexpr bool operator!=(const Matrix4& other) const
	{
		return !IsEqualApprox(other);
	}
};