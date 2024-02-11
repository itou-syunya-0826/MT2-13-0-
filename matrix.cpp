#include <Novice.h>
#include "matrix.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>


Matrix2x2 Add(Matrix2x2 matrix_1, Matrix2x2 matrix_2) {
	Matrix2x2 result{};
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result.m[i][j] = matrix_1.m[i][j] + matrix_2.m[i][j];
		}
	}
	return result;
}

Matrix2x2 Subtruct(Matrix2x2 matrix_1, Matrix2x2 matrix_2) {
	Matrix2x2 result{};
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result.m[i][j] = matrix_1.m[i][j] - matrix_2.m[i][j];
		}
	}
	return result;
}

Matrix2x2 Multiply(Matrix2x2 matrix_1, Matrix2x2 matrix_2) {
	Matrix2x2 result{};
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result.m[i][j] = 0;
			for (int k = 0; k < 2; k++) {
				result.m[i][j] += matrix_1.m[i][k] * matrix_2.m[k][j];
			}
		}
	}
	return result;
}

Matrix3x3 Multiply(Matrix3x3 matrix_1, Matrix3x3 matrix_2) {
	Matrix3x3 result{};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = 0;
			for (int k = 0; k < 3; k++) {
				result.m[i][j] += matrix_1.m[i][k] * matrix_2.m[k][j];
			}
		}
	}
	return result;
}

Vector2 Multiply(Vector2 vector, Matrix2x2 matrix_2) {
	Vector2 result{ 0.0f,0.0f };
	result.x = vector.x * matrix_2.m[0][0] + vector.y * matrix_2.m[1][0];
	result.y = vector.x * matrix_2.m[0][1] + vector.y * matrix_2.m[1][1];
	return result;
}

Matrix2x2 MakeRotateMatrix(float theta) {
	Matrix2x2 RotateMatrix = {};
	RotateMatrix.m[0][0] = cosf(theta);
	RotateMatrix.m[0][1] = sinf(theta);
	RotateMatrix.m[1][0] = -sinf(theta);
	RotateMatrix.m[1][1] = cosf(theta);
	return RotateMatrix;
}

Matrix3x3 MakeRotateMatrix2(float theta) {
	Matrix3x3 RotateMatrix = {};
	RotateMatrix.m[0][0] = cosf(theta);
	RotateMatrix.m[0][1] = sinf(theta);
	RotateMatrix.m[0][2] = 0;
	RotateMatrix.m[1][0] = -sinf(theta);
	RotateMatrix.m[1][1] = cosf(theta);
	RotateMatrix.m[1][2] = 0;
	RotateMatrix.m[2][0] = 0;
	RotateMatrix.m[2][1] = 0;
	RotateMatrix.m[2][2] = 1;
	return RotateMatrix;
}

Matrix3x3  MakeTrancelateMatrix(Vector2 trancelate) {
	Matrix3x3 TrancelateMatrix
	{1,0,0,
	0,1,0,
	trancelate.x,trancelate.y,1};
	
	return TrancelateMatrix;
}

Vector2 Tranceform(Vector2 vector, Matrix3x3 matrix) {
	Vector2 tranceform = {};
	tranceform.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	tranceform.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	tranceform.x /= w;
	tranceform.y /= w;
	return tranceform;
}

Vector2 Toscreen(Vector2 world) {
	const Vector2 kWorldToScreenTranslate = { 0.0f,500.0f };
	const Vector2 kWorldToScreenScale = { 1.0f,-1.0f };
	return{
		(world.x * kWorldToScreenScale.x) + kWorldToScreenTranslate.x,
		(world.y * kWorldToScreenScale.y) + kWorldToScreenTranslate.y
	};
}

Matrix2x2 Inverse(Matrix2x2 matrix ) {

	float Inverse = matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0] / 1;

	Matrix2x2 result{};

	result.m[0][0] = matrix.m[1][1];
	result.m[0][1] = -matrix.m[0][1];
	result.m[1][0] = -matrix.m[1][0];
	result.m[1][1] = matrix.m[0][0];

	Matrix2x2 resultInverse{};

	resultInverse.m[0][0] = result.m[0][0] / Inverse;
	resultInverse.m[0][1] = result.m[0][1] / Inverse;
	resultInverse.m[1][0] = result.m[1][0] / Inverse;
	resultInverse.m[1][1] = result.m[1][1] / Inverse;
	

	return resultInverse;
}

Matrix3x3 Inverse(Matrix3x3 matrix) {

	float detA = 
		matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
		matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] -
		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] -
		matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] -
		matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1];

	Matrix3x3 result{};

	result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]);
	result.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]);
	result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]);

	result.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]);
	result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]);
	result.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]);

	result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);
	result.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]);
	result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);
	





	Matrix3x3 resultInverse{};

	resultInverse.m[0][0] = result.m[0][0] / detA;
	resultInverse.m[0][1] = result.m[0][1] / detA;
	resultInverse.m[0][2] = result.m[0][2] / detA;

	resultInverse.m[1][0] = result.m[1][0] / detA;
	resultInverse.m[1][1] = result.m[1][1] / detA;
	resultInverse.m[1][2] = result.m[1][2] / detA;

	resultInverse.m[2][0] = result.m[2][0] / detA;
	resultInverse.m[2][1] = result.m[2][1] / detA;
	resultInverse.m[2][2] = result.m[2][2] / detA;

	return resultInverse;
}

Matrix2x2 transpose(Matrix2x2 matrix) {
	Matrix2x2 result{};
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result.m[i][j] = matrix.m[j][i];
		}
	}
	return result;
}

Matrix3x3 transpose(Matrix3x3 matrix) {
	Matrix3x3 result{};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = matrix.m[j][i];
		}
	}
	return result;
}

Matrix3x3 MakeOrthographicMatrix(float Left, float top, float Right, float bottom) {
	Matrix3x3 result
	{
		2.0f/ (Right - Left),0,0,
		0,2.0f / (top - bottom),0,
		(Left + Right) / (Left - Right),(top + bottom) / (bottom - top),1
	};

	return result;
}

Matrix3x3 MakeViewportMatrix(float Left, float top, float width, float height) {
	Matrix3x3 result
	{
		width / 2,0,0,
		0,-height / 2,0,
		Left + width / 2,top + height / 2,1
	};

	return result;
}

Vector2 Lerp(const Vector2& a, const Vector2& b, float t)
{
	Vector2 temp;

	temp.x= t * a.x + (1.0f - t) * b.x;
	temp.y= t * a.y + (1.0f - t) * b.y;
	return temp;

}

Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t) {
	
	Vector2 p0p1 = Lerp(p0,p1, t);
	Vector2 p1p2 = Lerp(p1,p2, t);
	Vector2 p = Lerp(p0p1, p1p2, t);

	return p;
	
}