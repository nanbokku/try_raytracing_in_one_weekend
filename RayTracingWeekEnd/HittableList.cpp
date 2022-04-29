#include "HittableList.h"

bool HittableList::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	HitRecord temp_rec{};
	bool hit_anything = false;
	auto closest_so_far = t_max;

	for (const auto& object : _objects)
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

bool HittableList::bounding_box(double t0, double t1, AABB& output_box) const
{
	if (_objects.empty())
	{
		return false;
	}

	AABB temp_box;
	bool first_box = true;

	for (const auto& object : _objects)
	{
		if (!object->bounding_box(t0, t1, temp_box))
		{
			return false;
		}

		output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
		first_box = false;
	}

	return true;
}