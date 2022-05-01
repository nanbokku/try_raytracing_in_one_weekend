#pragma once
#include "Hittable.h"

class Material;

class XZRect : public Hittable
{
public:
	XZRect() = default;

	XZRect(double _x0, double _x1, double _z0, double _z1, double _k, const std::shared_ptr<Material>& mat)
		:x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat)
	{
	}

	virtual bool hit(const Ray& r, double t0, double t1, HitRecord& rec) const;
	virtual bool bounding_box(double t0, double t1, AABB& output_box) const
	{
		// AABB‚Ì•Ó‚Ì’·‚³‚Íƒ[ƒ‚Å‚ ‚Á‚Ä‚Í‚È‚ç‚È‚¢‚½‚ßAy•ûŒü‚ÉŒú‚İ‚ğ‚½‚¹‚é
		output_box = AABB(Point3(x0, k - 0.0001, z0), Point3(x1, k + 0.0001, z1));
		return true;
	}

private:
	double x0, x1, z0, z1, k;
	std::shared_ptr<Material> mp;
};

