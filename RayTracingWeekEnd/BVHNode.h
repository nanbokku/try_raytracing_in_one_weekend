#pragma once

#include "HittableList.h"

class BVHNode : public Hittable
{
public:
	BVHNode();
	BVHNode(HittableList& list, double time0, double time1)
		:BVHNode(list.objects(), 0, list.objects().size(), time0, time1)
	{
	}
	BVHNode(std::vector<std::shared_ptr<Hittable>>& objects, size_t start, size_t end, double time0, double time1);

	virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
	virtual bool bounding_box(double t0, double t1, AABB& output_box) const;

private:
	std::shared_ptr<Hittable> left;
	std::shared_ptr<Hittable> right;
	AABB box;
};

inline bool box_compare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b, int axis)
{
	AABB box_a;
	AABB box_b;

	if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b))
	{
		std::cerr << "No bounding box in BVHNode constructor" << std::endl;
	}

	return box_a.min()[axis] < box_b.min()[axis];
}

bool box_x_compare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b)
{
	return box_compare(a, b, 0);
}

bool box_y_compare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b)
{
	return box_compare(a, b, 1);
}

bool box_z_compare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b)
{
	return box_compare(a, b, 2);
}