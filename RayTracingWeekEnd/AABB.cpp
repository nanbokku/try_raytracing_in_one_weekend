#include "AABB.h"

bool AABB::hit(const Ray& r, double t_min, double t_max) const
{
	for (int a = 0; a < 3; a++)
	{
		auto invD = 1.0 / r.direction()[a];
		auto t0 = (_min[a] - r.origin()[a]) * invD;
		auto t1 = (_max[a] - r.origin()[a]) * invD;

		if (invD < 0.0)
		{
			std::swap(t0, t1);
		}

		t_min = fmax(t0, t_min);
		t_max = fmin(t1, t_max);

		if (t_max <= t_min)
		{
			return false;
		}
	}

	return true;
}