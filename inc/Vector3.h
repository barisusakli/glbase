

#ifndef INC_VECTOR3_H
#define INC_VECTOR3_H

#include <cmath>

namespace glBase
{
	class Vector3
	{
	public:
		/// components of the vector
		union
		{
			struct{ float x,y,z; };
			struct{ float r,g,b; };
			float elements[3];
		};

		Vector3() { x=y=z=0.0f; }
		Vector3(const Vector3& v):x(v.x),y(v.y),z(v.z) { }
		Vector3(float x,float y,float z):x(x),y(y),z(z) { }

		Vector3& operator= (const Vector3& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			return *this;
		}

		bool operator ==(const Vector3 &v) const 
		{
			return x == v.x && y == v.y && z == v.z;
		}
		bool operator !=(const Vector3 &v) const 
		{
			return x != v.x || y != v.y || z != v.z;
		}

		void zero() { x = y = z = 0.0f; }
		Vector3 operator -() const { return Vector3(-x,-y,-z); }

		Vector3 operator +(const Vector3 &v) const { Vector3 r(*this); r+=v; return r; }
		Vector3 operator -(const Vector3 &v) const { Vector3 r(*this); r-=v; return r; }
		Vector3 operator *(float s) const { Vector3 r(*this); r*=s; return r; }
		Vector3 operator /(float a) const { Vector3 r(*this); r/=a; return r; }

		Vector3& operator +=(const Vector3& v) 
		{
			x += v.x; y += v.y; z += v.z;
			return *this;
		}
		Vector3& operator -=(const Vector3& v)
		{
			x -= v.x; y -= v.y; z -= v.z;
			return *this;
		}
		Vector3& operator *=(float s) 
		{
			x *= s; y *= s; z *= s;
			return *this;
		}
		Vector3& operator /=(float s) 
		{
			float recipS = 1.0f / s;
			x *= recipS; y *= recipS; z *= recipS;
			return *this;
		}

		void normalize();							///< Normalize vector		
		float operator *(const Vector3& v) const;	///< Vector dot product.

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & x;
			ar & y;
			ar & z;
		}
	};

	inline void Vector3::normalize()
	{
		float magnitudeSquared = x*x + y*y + z*z;
		if (magnitudeSquared > 0.0f) 
		{ 
			float oneOverMag = 1.0f / sqrt(magnitudeSquared);
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
		}
	}
	inline float Vector3::operator *(const Vector3& v) const 
	{
		return x*v.x + y*v.y + z*v.z;
	}

	/// Vector magnitude
	inline float vectorMagnitude(const Vector3& v) 
	{
		return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	}

	/// Compute the cross product of two vectors
	inline Vector3 crossProduct(const Vector3& a, const Vector3 &b) {
		return Vector3(
			a.y*b.z - a.z*b.y,
			a.z*b.x - a.x*b.z,
			a.x*b.y - a.y*b.x
			);
	}

	/// Scalar on the left multiplication, for symmetry
	inline Vector3 operator *(float k, const Vector3 &v) 
	{
		return Vector3(k*v.x, k*v.y, k*v.z);
	}

	/// Compute the euclidean distance between two vectors
	inline float distance(const Vector3 &a, const Vector3 &b) 
	{
		float dx = a.x - b.x;
		float dy = a.y - b.y;
		float dz = a.z - b.z;
		return sqrt(dx*dx + dy*dy + dz*dz);
	}
}



#endif //INC_VECTOR3_H