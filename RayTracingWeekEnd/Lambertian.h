#pragma once

#include "Material.h"

class Texture;

class Lambertian : public Material
{
public:
	Lambertian(const std::shared_ptr<Texture>& a)
		:albedo(a)
	{
	}

	virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const;

private:
	std::shared_ptr<Texture> albedo;
};