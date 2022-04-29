#include "Sphere.h"

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	Vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared();
	auto half_b = dot(r.direction(), oc);
	auto c = oc.length_squared() - radius * radius;
	auto discriminant = half_b * half_b - a * c;

	if (discriminant > 0)
	{
		auto root = sqrt(discriminant);
		auto t = (-half_b - root) / a;	// ˆêŒÂ–Ú‚ÌŒð“_

		if (t < t_max && t > t_min)
		{
			rec.t = t;
			rec.p = r.at(t);
			Vec3 outward_normal = (rec.p - center) / radius;
			rec.set_face_normal(r, outward_normal);
			rec.mat_ptr = mat_ptr;
			get_sphere_uv(outward_normal, rec.u, rec.v);

			return true;
		}

		t = (-half_b + root) / a;	// “ñŒÂ–Ú‚ÌŒð“_

		if (t < t_max && t > t_min)
		{
			rec.t = t;
			rec.p = r.at(t);
			Vec3 outward_normal = (rec.p - center) / radius;
			rec.set_face_normal(r, outward_normal);
			rec.mat_ptr = mat_ptr;
			get_sphere_uv(outward_normal, rec.u, rec.v);

			return true;
		}
	}

	return false;
}

bool Sphere::bounding_box(double t0, double t1, AABB& output_box) const
{
	output_box = AABB(center - Vec3(radius, radius, radius), center + Vec3(radius, radius, radius));
	return true;
}