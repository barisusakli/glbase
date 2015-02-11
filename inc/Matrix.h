//////////////////////////////////////////////////////////////////////////
//glBase OpenGL Application Framework
//
//Copyright http://glbase.codeplex.com/
//////////////////////////////////////////////////////////////////////////

#include "Vector3.h"

namespace glBase
{
	//Row major, 4x4 matrix
	class Matrix4x4
	{
	public:
		float elements[16];

		Matrix4x4() // Default constructor sets the matrix to the identity matrix
		{
			for(unsigned int i = 0; i < 16; i++)elements[i]=0.0f;
			elements[0] = elements[5] = elements[10] = elements[15] = 1.0f;
		}
		Matrix4x4(const Matrix4x4& m)
		{
			for(unsigned int i = 0; i < 16; i++)elements[i]=m.elements[i];
		}
		inline float& operator() (unsigned int row, unsigned int column)
		{
			return elements[row*4+column];
		}
		inline const float& operator() (unsigned int row, unsigned int column) const
		{
			return elements[row*4+column];
		}
		inline float determinant() const;

		static Matrix4x4 makeScaleMatrix(const Vector3& scale);
		static Matrix4x4 makeTranslationMatrix(const Vector3& translation);

		static Matrix4x4 makeRotationMatrixX(float radians);
		static Matrix4x4 makeRotationMatrixY(float radians);
		static Matrix4x4 makeRotationMatrixZ(float radians);
	};

	inline Matrix4x4 operator *(const Matrix4x4& lhs, const Matrix4x4& rhs)
	{
		Matrix4x4 result;

		for(unsigned int i=0; i < 4; i++)
		{
			for(unsigned int j=0; j < 4; j++)
			{
				result.elements[i] = lhs.elements[i*4  ] * rhs.elements[j] 
				+ lhs.elements[i*4+1] * rhs.elements[j+4] 
				+ lhs.elements[i*4+2] * rhs.elements[j+8] 
				+ lhs.elements[i*4+3] * rhs.elements[j+12];
			}
		}
		return result;
	}

	inline Vector3 operator *(const Matrix4x4& lhs, const Vector3& rhs)
	{
		Vector3 result;
		float invW =  1.0f / ( lhs.elements[12] * rhs.x + lhs.elements[13] * rhs.y + lhs.elements[14] * rhs.z + lhs.elements[15] );

		result.x = ( lhs.elements[0] * rhs.x + lhs.elements[1] * rhs.y + lhs.elements[2]  * rhs.z + lhs.elements[3]  ) * invW;
		result.y = ( lhs.elements[4] * rhs.x + lhs.elements[5] * rhs.y + lhs.elements[6]  * rhs.z + lhs.elements[7]  ) * invW;
		result.z = ( lhs.elements[8] * rhs.x + lhs.elements[9] * rhs.y + lhs.elements[10] * rhs.z + lhs.elements[11] ) * invW;
		return result;
	}

}