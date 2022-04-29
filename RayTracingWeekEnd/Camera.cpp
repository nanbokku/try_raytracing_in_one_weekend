#include "Camera.h"

Camera::Camera(const Point3& lookfrom, const Point3& lookat, const Vec3& vup, double vfov, double aspect_ratio, double aperture, double focus_dist, double t0, double t1)
{
	const double theta = degrees_to_radians(vfov);
	const double h = tan(theta / 2);
	const double viewport_height = 2.0 * h;
	const double viewport_width = aspect_ratio * viewport_height;

	w = unit_vector(lookfrom - lookat);
	u = unit_vector(cross(vup, w));
	v = cross(w, u);

	origin = lookfrom;
	horizontal = viewport_width * u * focus_dist;
	vertical = viewport_height * v * focus_dist;
	lower_left_corner = origin - horizontal / 2.0 - vertical / 2.0 - w * focus_dist;	// 右手座標系のため、奥行方向がZ-

	lens_radius = aperture / 2;
	time0 = t0;
	time1 = t1;
}