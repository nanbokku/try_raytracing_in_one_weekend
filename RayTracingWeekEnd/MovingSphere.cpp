#include "MovingSphere.h"

bool MovingSphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	Vec3 oc = r.origin() - center(r.time());
	auto a = r.direction().length_squared();
	auto half_b = dot(r.direction(), oc);
	auto c = oc.length_squared() - radius * radius;
	auto discriminant = half_b * half_b - a * c;

	if (discriminant > 0)
	{
		auto root = sqrt(discriminant);
		auto t = (-half_b - root) / a;

		if (t < t_max && t > t_min)
		{
			rec.t = t;
			rec.p = r.at(t);
			Vec3 outward_normal = (rec.p - center(r.time())) / radius;
			rec.set_face_normal(r, outward_normal);
			rec.mat_ptr = mat_ptr;
			return true;
		}

		t = (-half_b + root) / a;

		if (t < t_max && t > t_min)
		{
			rec.t = t;
			rec.p = r.at(t);
			Vec3 outward_normal = (rec.p - center(r.time())) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}

	return false;
}

Point3 MovingSphere::center(double time) const
{
	// time“_‚Å‚Ìcenter‚ğ‹‚ß‚é
	return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}