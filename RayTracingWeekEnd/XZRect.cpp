#include "XZRect.h"

bool XZRect::hit(const Ray& r, double t0, double t1, HitRecord& rec) const
{
	auto t = (k - r.origin().y()) / r.direction().y();

	if (t < t0 || t > t1)
	{
		return false;
	}

	auto x = r.origin().x() + t * r.direction().x();
	auto z = r.origin().z() + t * r.direction().z();

	if (x < x0 || x > x1 || z < z0 || z > z1)
	{
		return false;
	}

	rec.u = (x - x0) / (x1 - x0);
	rec.v = (z - z0) / (z1 - z0);
	rec.t = t;
	auto outward_normal = Vec3(0, 1, 0);
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mp;
	rec.p = r.at(t);

	return true;
}