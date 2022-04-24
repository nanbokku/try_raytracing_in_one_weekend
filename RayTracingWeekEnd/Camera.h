#pragma once

#include "rtweekend.h"

class Camera
{
public:
	Camera();

	Ray get_ray(double u, double v) const
	{
		return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
	}

private:
	Point3 origin{ 0,0,0 };
	Point3 lower_left_corner{ 0,0,0 };
	Vec3 horizontal{ 0,0,0 };
	Vec3 vertical{ 0,0,0 };
};

