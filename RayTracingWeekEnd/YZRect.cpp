#include "YZRect.h"

bool YZRect::hit(const Ray& r, double t0, double t1, HitRecord& rec) const
{
	auto t = (k - r.origin().x()) / r.direction().x();

	if (t < t0 || t > t1)
	{
		return false;
	}

	auto y = r.origin().y() + t * r.direction().y();
	auto z = r.origin().z() + t * r.direction().z();

	if (y < y0 || y > y1 || z < z0 || z > z1)
	{
		return false;
	}

	rec.u = (y - y0) / (y1 - y0);
	rec.v = (z - z0) / (z1 - z0);
	rec.t = t;
	auto outward_normal = Vec3(1, 0, 0);
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mp;
	rec.p = r.at(t);

	return true;
}