#pragma once
#include "Hittable.h"

class Material;

class MovingSphere : public Hittable
{
public:
	MovingSphere() = default;
	MovingSphere(const Point3& cen0, const Point3& cen1, double t0, double t1, double r, std::shared_ptr<Material> m)
		: center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(m)
	{
	}

	virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;

	Point3 center(double time) const;

private:
	Point3 center0{ 0,0,0 };
	Point3 center1{ 0,0,0 };
	double time0, time1;
	double radius;
	std::shared_ptr<Material> mat_ptr;
};

