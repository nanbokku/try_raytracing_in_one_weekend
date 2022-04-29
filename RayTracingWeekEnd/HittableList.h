#pragma once

#include "Hittable.h"

#include <memory>
#include <vector>


class HittableList : public Hittable
{
public:
	HittableList() = default;
	HittableList(std::shared_ptr<Hittable> object)
	{
		add(object);
	}

	void clear() { _objects.clear(); }
	void add(std::shared_ptr<Hittable> object) { _objects.push_back(object); }

	virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
	virtual bool bounding_box(double t0, double t1, AABB& output_box) const;

	std::vector<std::shared_ptr<Hittable>> objects() const { return _objects; }
	std::vector<std::shared_ptr<Hittable>>& objects() { return _objects; }

private:
	std::vector<std::shared_ptr<Hittable>> _objects{};
};