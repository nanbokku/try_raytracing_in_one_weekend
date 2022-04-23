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

	void clear() { objects.clear(); }
	void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }

	virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;

private:
	std::vector<std::shared_ptr<Hittable>> objects{};
};