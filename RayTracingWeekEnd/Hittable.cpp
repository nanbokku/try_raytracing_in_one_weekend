#include "Hittable.h"

bool Translate::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	Ray r_moved(r.origin() - offset, r.direction(), r.time());

	if (!ptr->hit(r_moved, t_min, t_max, rec))
	{
		return false;
	}

	rec.p += offset;
	rec.set_face_normal(r_moved, rec.normal);

	return true;
}

bool Translate::bounding_box(double t0, double t1, AABB& output_box) const
{
	if (!ptr->bounding_box(t0, t1, output_box))
	{
		return false;
	}

	output_box = AABB(output_box.min() + offset, output_box.max() + offset);
	return true;
}

RotateY::RotateY(const std::shared_ptr<Hittable>& p, double angle)
	:ptr(p)
{
	auto radians = degrees_to_radians(angle);
	sin_theta = sin(radians);
	cos_theta = cos(radians);
	hasbox = p->bounding_box(0, 1, bbox);
	Point3 min(infinity, infinity, infinity);
	Point3 max(-infinity, -infinity, -infinity);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				auto x = i * bbox.max().x() + (1 - i) * bbox.min().x();
				auto y = j * bbox.max().y() + (1 - j) * bbox.min().y();
				auto z = k * bbox.max().z() + (1 - k) * bbox.min().z();
				auto newx = cos_theta * x + sin_theta * z;
				auto newz = -sin_theta * x + cos_theta * z;

				Vec3 tester(newx, y, newz);

				for (int c = 0; c < 3; c++)
				{
					min[c] = fmin(min[c], tester[c]);
					max[c] = fmax(max[c], tester[c]);
				}
			}
		}
	}

	bbox = AABB(min, max);
}

bool RotateY::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	auto origin = r.origin();
	auto direction = r.direction();
	origin[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[2];
	origin[2] = sin_theta * r.origin()[0] + cos_theta * r.origin()[2];
	direction[0] = cos_theta * r.direction()[0] - sin_theta * r.direction()[2];
	direction[2] = sin_theta * r.direction()[0] + cos_theta * r.direction()[2];

	// オブジェクトの回転の逆回転をしたレイを使って衝突判定
	Ray rotated_r(origin, direction, r.time());

	if (!ptr->hit(rotated_r, t_min, t_max, rec))
	{
		return false;
	}

	auto p = rec.p;
	auto normal = rec.normal;

	// 回転後の座標/ベクトルを計算
	p[0] = cos_theta * rec.p[0] + sin_theta * rec.p[2];
	p[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];

	normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
	normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

	rec.p = p;
	rec.normal = normal;

	return true;
}