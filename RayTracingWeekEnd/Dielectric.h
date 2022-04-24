#pragma once
#include "Material.h"

class Dielectric : public Material
{
public:
	Dielectric(double ri)
		: ref_idx(ri)
	{
	}

	virtual bool scatter(const Ray& r, const HitRecord& rec, Color& attenuation, Ray& scattered) const;

private:
	double ref_idx;
};

