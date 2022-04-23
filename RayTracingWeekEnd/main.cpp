#include <iostream>
#include <fstream>

#include "Color.h"
#include "Ray.h"


bool hit_sphere(const Point3& center, double radius, const Ray& r)
{
	Vec3 oc = r.origin() - center;
	auto a = dot(r.direction(), r.direction());
	auto b = 2.0 * dot(r.direction(), oc);
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4.0 * a * c;
	return discriminant >= 0;
}

Color ray_color(const Ray& r)
{
	if (hit_sphere(Point3(0, 0, -1), 0.5, r))
	{
		return Color(1.0, 0.0, 0.0);	// 赤い球
	}

	Vec3 unit_direction = unit_vector(r.direction());
	double t = 0.5 * (unit_direction.y() + 1.0);	// [-1,1] -> [0,1]に変換
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);	// 青と白のグラデ
}


int main()
{
	constexpr double aspect_ratio = 16.0 / 9.0;
	constexpr int image_width = 256;
	constexpr int image_height = static_cast<int>(image_width / aspect_ratio);

	std::ofstream file("image.ppm");

	file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	constexpr double viewport_height = 2.0;
	constexpr double viewport_width = aspect_ratio * viewport_height;
	constexpr double focal_length = 1.0;

	auto origin = Point3(0, 0, 0);
	auto horizontal = Vec3(viewport_width, 0, 0);
	auto vertical = Vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);	// 右手座標系のため、奥行方向がZ-

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

		for (int i = 0; i < image_width; ++i)
		{
			double u = double(i) / (image_width - 1);
			double v = double(j) / (image_height - 1);
			Ray ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);

			Color pixel_color = ray_color(ray);
			write_color(file, pixel_color);
		}
	}

	std::cerr << "\nDone.\n";

	return 0;
}