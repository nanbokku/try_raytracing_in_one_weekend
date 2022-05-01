#pragma once
#include "Hittable.h"
#include "HittableList.h"

class Box : public Hittable
{
public:
	Box() = default;
	Box(const Point3& p0, const Point3& p1, const std::shared_ptr<Material>& ptr);

	virtual bool hit(const Ray& r, double t0, double t1, HitRecord& rec) const override;
	virtual bool bounding_box(double t0, double t1, AABB& output_box) const override
	{
		output_box = AABB(box_min, box_max);
		return true;
	}

private:
	Point3 box_min;
	Point3 box_max;
	HittableList sides;
};

