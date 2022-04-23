#pragma once

#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable
{
public:
	Sphere() = default;
	Sphere(const Point3& cen, double r)
		:center(cen), radius(r)
	{
	}

	virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;

private:
	Point3 center{ 0,0,0 };
	double radius{ 0 };
};