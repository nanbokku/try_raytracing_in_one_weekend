#pragma once

#include "Ray.h"

class AABB
{
public:
	AABB() = default;
	AABB(const Point3& a, const Point3& b)
	{
		_min = a;
		_max = b;
	}

	bool hit(const Ray& r, double t_min, double t_max) const;

	Point3 min() const { return _min; }
	Point3 max() const { return _max; }

private:
	Point3 _min{};
	Point3 _max{};
};

inline AABB surrounding_box(const AABB& a, const AABB& b)
{
	Point3 small(fmin(a.min().x(), b.min().x()), fmin(a.min().y(), b.min().y()), fmin(a.min().z(), b.min().z()));
	Point3 big(fmax(a.max().x(), b.max().x()), fmax(a.max().y(), b.max().y()), fmax(a.max().z(), b.max().z()));

	return AABB(small, big);
}