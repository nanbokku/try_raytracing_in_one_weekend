#pragma once

#include "Hittable.h"
#include "Isotropic.h"

class Texture;

class ConstantMedium : public Hittable
{
public:
	ConstantMedium(const std::shared_ptr<Hittable>& b, double d, const std::shared_ptr<Texture>& a)
		:boundary(b), neg_inv_density(-1 / d)
	{
		phase_function = std::make_shared<Isotropic>(a);
	}

	virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

	virtual bool bounding_box(double t0, double t1, AABB& output_box) const override
	{
		return boundary->bounding_box(t0, t1, output_box);
	}

private:
	std::shared_ptr<Hittable> boundary;
	std::shared_ptr<Material> phase_function;
	double neg_inv_density;
};