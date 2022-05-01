#pragma once

#include "AABB.h"

class Material;

struct HitRecord
{
	Point3 p;
	Vec3 normal;
	std::shared_ptr<Material> mat_ptr;
	double t;
	double u;	// テクスチャ座標U
	double v;	// テクスチャ座標V
	bool front_face;

	inline void set_face_normal(const Ray& r, const Vec3& outward_normal)
	{
		front_face = dot(r.direction(), outward_normal) < 0.0;
		normal = front_face ? outward_normal : -outward_normal;	// 裏側の場合は法線を反転
	}
};

class Hittable
{
public:
	virtual ~Hittable() = default;
	virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
	virtual bool bounding_box(double t0, double t1, AABB& output_box) const = 0;
};

class Translate : public Hittable
{
public:
	Translate(const std::shared_ptr<Hittable>& p, const Vec3& displacement)
		:ptr(p), offset(displacement)
	{
	}

	virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
	virtual bool bounding_box(double t0, double t1, AABB& output_box) const override;

private:
	std::shared_ptr<Hittable> ptr;
	Vec3 offset;
};

class RotateY : public Hittable
{
public:
	RotateY(const std::shared_ptr<Hittable>& p, double angle);

	virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
	virtual bool bounding_box(double t0, double t1, AABB& output_box) const override
	{
		output_box = bbox;
		return true;
	}

private:
	std::shared_ptr<Hittable> ptr;
	double sin_theta;
	double cos_theta;
	bool hasbox;
	AABB bbox;
};