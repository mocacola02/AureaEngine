#pragma once

#include "Int.h"
#include "Vector3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//! 4x4 Matrix with 32-bit float precision
struct Matrix4F
{
	float data[16] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	Matrix4F() = default;

	explicit Matrix4F(const glm::mat4& matrix)
	{
		for (uint8 column = 0; column < 4; ++column)
		{
			for (uint8 row = 0; row < 4; ++row)
			{
				data[column * 4 + row] = matrix[column][row];
			}
		}
	}

	static constexpr Matrix4F Identity()
	{
		return Matrix4F(glm::mat4(1.0f));
	}
};