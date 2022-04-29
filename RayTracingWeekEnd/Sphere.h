#pragma once

#include "Hittable.h"

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
	virtual bool bounding_box(double t0, double t1, AABB& output_box) const;

private:
	Point3 center{ 0,0,0 };
	double radius{ 0 };
	std::shared_ptr<Material> mat_ptr;
};

inline void get_sphere_uv(const Vec3& p, double& u, double& v)
{
	auto phi = atan2(p.z(), p.x());	// -pi ~ pi
	auto theta = asin(p.y());	// -pi/2 ~ pi/2
	u = 1 - (phi + pi) / (2.0 * pi);	// ‚’¼ã•ûŒü‚ª³
	v = (theta + pi / 2) / pi;
}