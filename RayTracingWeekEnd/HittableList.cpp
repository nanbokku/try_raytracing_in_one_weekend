#include "HittableList.h"

bool HittableList::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	HitRecord temp_rec{};
	bool hit_anything = false;
	auto closest_so_far = t_max;

	for (const auto& object : objects)
	{
		if (object->hit(r, t_min, closest_so_far, temp_rec))	// 全オブジェクトを探索して、一番近くで衝突する点を見つける
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}