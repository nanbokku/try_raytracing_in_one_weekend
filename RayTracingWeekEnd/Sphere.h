#pragma once

#include "Hittable.h"
#include "Vec3.h"

class Material;

class Sphere : public Hittable
{
public:
	Sphere() = default;
	Sphere(const Point3& cen, double r, std::shared_ptr<Material> m)
		:center(cen), radius(r), mat_ptr(m)
	{
	}

	virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;

private:
	Point3 center{ 0,0,0 };
	double radius{ 0 };
	std::shared_ptr<Material> mat_ptr;
};