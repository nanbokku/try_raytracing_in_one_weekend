#include <iostream>
#include <fstream>

#include "rtweekend.h"

#include "HittableList.h"
#include "Sphere.h"
#include "Color.h"
#include "Camera.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"


Color ray_color(const Ray& r, const Hittable& world, int depth)
{
	HitRecord rec{};

	// 反射回数が一定よりも多くなったら、その時点で追跡をやめる
	if (depth <= 0)
	{
		return Color(0, 0, 0);
	}

	if (world.hit(r, 0.001, infinity, rec))
	{
		Ray scattered;
		Color attenuation;

		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * ray_color(scattered, world, depth - 1);
		}

		return Color(0, 0, 0);
	}

	Vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);	// [-1,1] -> [0,1]に変換
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);	// 青と白のグラデ
}


int main()
{
	constexpr double aspect_ratio = 16.0 / 9.0;
	constexpr int image_width = 256;
	constexpr int image_height = static_cast<int>(image_width / aspect_ratio);
	constexpr int samples_per_pixel = 100;
	constexpr int max_depth = 50;

	std::ofstream file("image.ppm");

	file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	Camera cam{ 90, double(image_width / image_height) };

	HittableList world{};
	world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5, std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5))));
	world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100, std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0))));
	world.add(std::make_shared<Sphere>(Point3(1, 0, -1), 0.5, std::make_shared<Metal>(Color(.8, .6, .2), 0.3)));
	world.add(std::make_shared<Sphere>(Point3(-1, 0, -1), 0.5, std::make_shared<Dielectric>(1.5)));
	world.add(std::make_shared<Sphere>(Point3(-1, 0, -1), -0.45, std::make_shared<Dielectric>(1.5)));

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

		for (int i = 0; i < image_width; ++i)
		{
			Color pixel_color{ 0,0,0 };

			for (int s = 0; s < samples_per_pixel; ++s)
			{
				double u = double(i + random_double()) / (image_width - 1);
				double v = double(j + random_double()) / (image_height - 1);
				Ray ray = cam.get_ray(u, v);

				pixel_color += ray_color(ray, world, max_depth);
			}

			write_color(file, pixel_color, samples_per_pixel);
		}
	}

	std::cerr << "\nDone.\n";

	return 0;
}