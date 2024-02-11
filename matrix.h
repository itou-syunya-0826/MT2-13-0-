#pragma once

typedef struct Matrix2x2 {
	float m[2][2];
}Matrix2x2;

typedef struct Matrix3x3 {
	float m[3][3];
}Matrix3x3;

typedef struct Vector2 {
	float x;
	float y;
}Vector2;

typedef struct Vertex {
	Vector2 LeftTop;
	Vector2 LeftBottom;
	Vector2 RightTop;
	Vector2 RightBottom;
}Vertex;

typedef struct Line {
	Vector2 begin;
	Vector2 end;
}Line;

typedef struct Ball {
	Vector2 Pos;
	Vector2 Acceleration;
	Vector2 Velocity;
	Vector2 Local;
	Vector2 Screen;
	float Radius;
	float Mass;
	unsigned int Color;
	Matrix3x3 WorldMatrix;
	Matrix3x3 WvpVpMatrix;
}Ball;




Matrix2x2 Add(Matrix2x2 matrix_1, Matrix2x2 matrix_2);
Matrix2x2 Subtruct(Matrix2x2 matrix_1, Matrix2x2 matrix_2);
Matrix2x2 Multiply(Matrix2x2 matrix_1, Matrix2x2 matrix_2);
Matrix3x3 Multiply(Matrix3x3 matrix_1, Matrix3x3 matrix_2);
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix_2);
Matrix2x2 MakeRotateMatrix(float theta);
Matrix3x3 MakeRotateMatrix2(float theta);
Matrix3x3 MakeTrancelateMatrix(Vector2 trancelate);
Vector2 Tranceform(Vector2 vector, Matrix3x3 matrix);
Vector2 Toscreen(Vector2 world);
Matrix2x2 Inverse(Matrix2x2 matrix);
Matrix3x3 Inverse(Matrix3x3 matrix);
Matrix2x2 transpose(Matrix2x2 matrix);
Matrix3x3 transpose(Matrix3x3 matrix);
Matrix3x3 MakeOrthographicMatrix(float Left, float top, float Right, float bottom);
Matrix3x3 MakeViewportMatrix(float Left, float top, float width, float height);
Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t);


