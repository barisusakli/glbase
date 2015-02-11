//////////////////////////////////////////////////////////////////////////
//glBase OpenGL Application Framework
//
//Copyright http://glbase.codeplex.com/
//////////////////////////////////////////////////////////////////////////

#include "Matrix.h"

using namespace glBase;

Matrix4x4 Matrix4x4::makeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 result;
	result.elements[0] = scale.x;
	result.elements[5] = scale.y;
	result.elements[10] = scale.z;
	return result;
}
Matrix4x4 Matrix4x4::makeTranslationMatrix(const Vector3& translation)
{
	Matrix4x4 result;
	result.elements[3]  = translation.x;
	result.elements[7]  = translation.y;
	result.elements[11] = translation.z;
	return result;
}
Matrix4x4 Matrix4x4::makeRotationMatrixX(float radians)
{
	Matrix4x4 result;
	result(1,1) = cos(radians);
	result(2,2) = cos(radians);
	result(1,2) =-sin(radians);
	result(2,1) = sin(radians);
	return result;
}
Matrix4x4 Matrix4x4::makeRotationMatrixY(float radians)
{
	Matrix4x4 result;
	result(0,0) = cos(radians);
	result(2,2) = cos(radians);
	result(0,2) =-sin(radians);
	result(2,0) = sin(radians);
	return result;
}
Matrix4x4 Matrix4x4::makeRotationMatrixZ(float radians)
{
	Matrix4x4 result;
	result(0,0) = cos(radians);
	result(1,1) = cos(radians);
	result(0,1) =-sin(radians);
	result(1,0) = sin(radians);
	return result;
}