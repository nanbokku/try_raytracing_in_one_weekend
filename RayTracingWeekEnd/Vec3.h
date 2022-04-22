#pragma once

#include <cmath>
#include <iostream>

using std::sqrt;

class Vec3
{
public:
	Vec3() = default;
	Vec3(double e0, double e1, double e2)
		:e{ e0,e1,e2 }
	{
	}

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
	double operator[](const int i) const { return e[i]; }
	double& operator[](const int i) { return e[i]; }
	Vec3& operator*=(const double t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}
	Vec3& operator/=(const double t)
	{
		return *this *= 1 / t;
	}
	
	double length() const { return sqrt(length_squared()); }
	double length_squared() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

private:
	double e[3]{ 0,0,0 };
};


using Point3 = Vec3;	// 3Dì_
using Color = Vec3;		// RGBêF


// utilities
inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
	out << v.x() << ' ' << v.y() << ' ' << v.z();
	return out;
}
inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
	return Vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}
inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
	return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}
inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
	return Vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}
inline Vec3 operator*(double t, const Vec3& v)
{
	return Vec3(t * v.x(), t * v.y(), t * v.z());
}
inline Vec3 operator*(const Vec3& v, double t)
{
	return t * v;
}
inline Vec3 operator/(const Vec3& v, double t)
{
	return (1 / t) * v;
}
inline double dot(const Vec3& u, const Vec3& v)
{
	return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}
inline Vec3 cross(const Vec3& u, const Vec3& v)
{
	return Vec3(u.y() * v.z() - u.z() * v.y(), u.z() * v.x() - u.x() * v.z(), u.x() * v.y() - u.y() * v.x());
}
inline Vec3 unit_vector(const Vec3& v)
{
	return v / v.length();
}