#pragma once

#include "rtweekend.h"

class Camera
{
public:
	Camera(const Point3& lookfrom,
		const Point3& lookat,
		const Vec3& vup,
		double vfov,		// 垂直方向の視野角（弧度法）
		double aspect_ratio,
		double aperture,
		double focus_dist);

	Ray get_ray(double s, double t) const
	{
		const Vec3 rd = lens_radius * random_in_unit_disk();
		const Vec3 offset = u * rd.x() + v * rd.y();

		return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
	}

private:
	Point3 origin{ 0,0,0 };
	Point3 lower_left_corner{ 0,0,0 };
	Vec3 horizontal{ 0,0,0 };
	Vec3 vertical{ 0,0,0 };
	Vec3 u, v, w;
	double lens_radius{ 0 };
};

