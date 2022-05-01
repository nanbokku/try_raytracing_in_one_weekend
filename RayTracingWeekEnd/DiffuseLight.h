#pragma once
#include "Material.h"
#include "Texture.h"

class DiffuseLight : public Material
{
public:
	DiffuseLight(const std::shared_ptr<Texture>& a)
		: emit(a)
	{
	}
	DiffuseLight(const Color& c)
		:emit(std::make_shared<SolidColor>(c))
	{
	}

	virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
	{
		// ”½ŽËƒŒƒC‚ðŒvŽZ‚µ‚È‚¢
		return false;
	}

	virtual Color emitted(double u, double v, const Point3& p) const
	{
		return emit->value(u, v, p);
	}

private:
	std::shared_ptr<Texture> emit;
};

