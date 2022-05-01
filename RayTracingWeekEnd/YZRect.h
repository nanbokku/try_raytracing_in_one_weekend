#pragma once
#include "Hittable.h"

class Material;

class YZRect : public Hittable
{
public:
	YZRect() = default;

	YZRect(double _y0, double _y1, double _z0, double _z1, double _k, const std::shared_ptr<Material>& mat)
		:y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat)
	{
	}

	virtual bool hit(const Ray& r, double t0, double t1, HitRecord& rec) const;
	virtual bool bounding_box(double t0, double t1, AABB& output_box) const
	{
		// AABB‚Ì•Ó‚Ì’·‚³‚Íƒ[ƒ‚Å‚ ‚Á‚Ä‚Í‚È‚ç‚È‚¢‚½‚ßAx•ûŒü‚ÉŒú‚İ‚ğ‚½‚¹‚é
		output_box = AABB(Point3(k - 0.0001, y0, z0), Point3(k + 0.0001, y1, z1));
		return true;
	}

private:
	double y0, y1, z0, z1, k;
	std::shared_ptr<Material> mp;
};

