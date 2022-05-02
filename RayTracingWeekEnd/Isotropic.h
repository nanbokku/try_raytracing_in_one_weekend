#pragma once

#include "Material.h"
#include "Texture.h"

class Isotropic : public Material
{
public:
	Isotropic(const std::shared_ptr<Texture>& a)
		:albedo(a)
	{
	}

	virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override
	{
		// Isotropic(������)�e�N�X�`����scatter�֐��͕�������l�����_���ɑI��
		scattered = Ray(rec.p, random_in_unit_sphere(), r_in.time());
		attenuation = albedo->value(rec.u, rec.v, rec.p);

		return true;
	}

private:
	std::shared_ptr<Texture> albedo;
};