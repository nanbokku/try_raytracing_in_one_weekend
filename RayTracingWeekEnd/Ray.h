#pragma once

#include "Vec3.h"

class Ray
{
public:
	Ray() = default;
	Ray(const Point3& origin, const Vec3& direction, double time = 0.0)
		:orig(origin), dir(direction), tm(time)
	{
	};

	Point3 origin() const { return orig; }
	Vec3 direction() const { return dir; }
	double time() const { return tm; }

	Point3 at(double t) const
	{
		return orig + t * dir;
	}

private:
	Point3 orig{ 0,0,0 };
	Vec3 dir{ 0,0,0 };	// ì¡Ç…ê≥ãKâªÇÕÇµÇ»Ç¢ÅiçÇë¨âªÇÃÇΩÇﬂÅj
	double tm{ 0 };
};