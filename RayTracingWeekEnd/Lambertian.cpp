#include "Lambertian.h"

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
	Vec3 scatter_direction = rec.normal + random_unit_vector();
	scattered = Ray(rec.p, scatter_direction);
	attenuation = albedo;
	return true;
}