#pragma once

#include <cmath>
#include <iostream>
#include "rtweekend.h"

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
	Vec3& operator+=(const Vec3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	double length() const { return std::sqrt(length_squared()); }
	double length_squared() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}
	bool near_zero() const
	{
		const auto s = 1e-8;
		return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
	}

	inline static Vec3 random()
	{
		return Vec3(random_double(), random_double(), random_double());
	}

	inline static Vec3 random(double min, double max)
	{
		return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}

private:
	double e[3]{ 0,0,0 };
};


using Point3 = Vec3;	// 3D“_
using Color = Vec3;		// RGBF


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
inline Vec3 random_in_unit_sphere()
{
	while (true)
	{
		auto p = Vec3::random(-1, 1);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}
inline Vec3 random_unit_vector()
{
	auto theta = random_double(0, 2 * pi);	// Œo“x
	auto y = random_double(-1, 1);	// ‚‚³
	auto r = std::sqrt(1.0 - y * y);	// XZ•½–Ê‚ÅŒ©‚½Žž‚Ì‰~‚Ì”¼Œa

	return Vec3(r * cos(theta), y, r * sin(theta));
}
inline Vec3 random_in_hemisphere(const Vec3& normal)
{
	Vec3 in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0)
	{
		return in_unit_sphere;	// “¯‚¶”¼‹…‚É‚ ‚é
	}
	else
	{
		return -in_unit_sphere;
	}
}
inline Vec3 reflect(const Vec3& v, const Vec3& n)
{
	return v - 2 * dot(v, n) * n;
}
inline Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat)
{
	auto cos_theta = dot(-uv, n);
	Vec3 r_out_parallel = etai_over_etat * (uv + cos_theta * n);
	Vec3 r_out_perp = -std::sqrt(1 - r_out_parallel.length_squared()) * n;
	return r_out_parallel + r_out_perp;
}
inline Vec3 random_in_unit_disk()
{
	while (true)
	{
		auto p = Vec3(random_double(-1, 1), random_double(-1, 1), 0);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}