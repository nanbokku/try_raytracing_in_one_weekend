#pragma once

#include "Vec3.h"

class Ray
{
public:
	Ray() = default;
	Ray(const Point3& origin, const Vec3& direction)
		:orig(origin), dir(direction)
	{
	};

	Point3 origin() const { return orig; }
	Vec3 direction() const { return dir; }

	Point3 at(double t) const
	{
		return orig + t * dir;
	}

private:
	Point3 orig{ 0,0,0 };
	Vec3 dir{ 0,0,0 };	// ì¡Ç…ê≥ãKâªÇÕÇµÇ»Ç¢ÅiçÇë¨âªÇÃÇΩÇﬂÅj
};