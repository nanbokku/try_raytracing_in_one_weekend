#include "Camera.h"

Camera::Camera(double vfov, double aspect_ratio)
{
	constexpr double viewport_height = 2.0;
	constexpr double viewport_width = aspect_ratio * viewport_height;
	constexpr double focal_length = 1.0;

	origin = Point3(0, 0, 0);
	horizontal = Vec3(viewport_width, 0, 0);
	vertical = Vec3(0, viewport_height, 0);
	lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - Vec3(0, 0, focal_length);	// 右手座標系のため、奥行方向がZ-
}