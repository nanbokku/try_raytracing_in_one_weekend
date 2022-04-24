#include "Dielectric.h"


double schlick(double cosine, double ref_idx)
{
	auto r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool Dielectric::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
	attenuation = Color(1.0, 1.0, 1.0);	// �K���X���͌����z�����Ȃ����߁A�����͏��1
	double etai_over_etat = (rec.front_face) ? (1.0 / ref_idx) : ref_idx;

	Vec3 unit_direction = unit_vector(r_in.direction());
	double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
	double sin_theta = sqrt(1 - cos_theta * cos_theta);

	if (etai_over_etat * sin_theta > 1.0) // �S����
	{
		Vec3 reflected = reflect(unit_direction, rec.normal);
		scattered = Ray(rec.p, reflected);
		return true;
	}

	// ���˗��̋ߎ��i�V�����b�N�̋ߎ��j
	double reflect_prob = schlick(cos_theta, etai_over_etat);

	if (random_double() < reflect_prob)
	{
		Vec3 reflected = reflect(unit_direction, rec.normal);
		scattered = Ray(rec.p, reflected);
		return true;
	}

	Vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
	scattered = Ray(rec.p, refracted);

	return true;
}