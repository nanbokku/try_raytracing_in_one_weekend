#pragma once

#include "Hittable.h"

class Material;

class XYRect : public Hittable
{
public:
	XYRect() = default;

	XYRect(double _x0, double _x1, double _y0, double _y1, double _k, const std::shared_ptr<Material>& mat)
		:x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat)
	{
	}

	virtual bool hit(const Ray& r, double t0, double t1, HitRecord& rec) const;

	virtual bool bounding_box(double t0, double t1, AABB& output_box) const
	{
		// AABB‚Ì•Ó‚Ì’·‚³‚Íƒ[ƒ‚Å‚ ‚Á‚Ä‚Í‚È‚ç‚È‚¢‚½‚ßAz•ûŒü‚É­‚µŒú‚İ‚ğ‚½‚¹‚é
		output_box = AABB(Point3(x0, y0, k - 0.0001), Point3(x1, y1, k + 0.0001));
		return true;
	}

private:
	double x0, x1, y0, y1, k;
	std::shared_ptr<Material> mp;
};