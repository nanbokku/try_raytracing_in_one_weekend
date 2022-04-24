#pragma once

#include "Material.h"

class Lambertian : public Material
{
public:
	Lambertian(const Color& a)
		:albedo(a)
	{
	}

	virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const;

private:
	Color albedo;
};