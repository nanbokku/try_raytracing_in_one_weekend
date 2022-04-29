#include <iostream>
#include <fstream>

#include "rtweekend.h"

#include "HittableList.h"
#include "Sphere.h"
#include "MovingSphere.h"
#include "Color.h"
#include "Camera.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "Texture.h"


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

HittableList random_scene()
{
	HittableList world{};

	auto ground_material = std::make_shared<Lambertian>(std::make_shared<CheckerTexture>(std::make_shared<SolidColor>(Color(0.2, 0.3, 0.1)), std::make_shared<SolidColor>(Color(0.9, 0.9, 0.9))));
	world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			auto choose_mat = random_double();
			Point3 center{ a + 0.9 * random_double(), 0.2, b + 0.9 * random_double() };	// a,bと乱数を基に値を決める

			if ((center - Vec3(4, 0.2, 0)).length() > 0.9)	// (4,0.2,0)とcenterとの間隔をあける
			{
				std::shared_ptr<Material> sphere_material;

				if (choose_mat < 0.8)
				{
					// diffuse
					auto albedo = std::make_shared<SolidColor>(Color::random() * Color::random());
					sphere_material = std::make_shared<Lambertian>(albedo);
					auto center2 = center + Vec3(0, random_double(0, 0.5), 0);
					world.add(std::make_shared<MovingSphere>(center, center2, 0, 1, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95)
				{
					// metal
					auto albedo = Color::random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = std::make_shared<Metal>(albedo, fuzz);
					world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else
				{
					// glass
					sphere_material = std::make_shared<Dielectric>(1.5);
					world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = std::make_shared<Dielectric>(1.5);
	world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1, material1));
	auto material2 = std::make_shared<Lambertian>(std::make_shared<SolidColor>(Color(0.4, 0.2, 0.1)));
	world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1, material2));
	auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0);
	world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1, material3));

	return world;
}

HittableList two_spheres()
{
	HittableList objects{};

	auto checker = std::make_shared<CheckerTexture>(
		std::make_shared<SolidColor>(0.2, 0.3, 0.1),
		std::make_shared<SolidColor>(0.9, 0.9, 0.9)
	);

	objects.add(std::make_shared<Sphere>(Point3(0, -10, 0), 10, std::make_shared<Lambertian>(checker)));
	objects.add(std::make_shared<Sphere>(Point3(0, 10, 0), 10, std::make_shared<Lambertian>(checker)));

	return objects;
}

HittableList two_perlin_spheres()
{
	HittableList objects{};

	auto pertext = std::make_shared<NoiseTexture>(5);

	objects.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, std::make_shared<Lambertian>(pertext)));
	objects.add(std::make_shared<Sphere>(Point3(0, 2, 0), 2, std::make_shared<Lambertian>(pertext)));

	return objects;
}

int main(int argc, char* argv[])
{
	constexpr double aspect_ratio = 16.0 / 9.0;
	constexpr int image_width = 256;
	constexpr int image_height = static_cast<int>(image_width / aspect_ratio);
	constexpr int samples_per_pixel = 100;
	constexpr int max_depth = 50;
	const Point3 lookfrom{ 13,2,3 };
	const Point3 lookat{ 0,0,0 };
	const Vec3 vup{ 0,1,0 };
	const double dist_to_focus = 10;
	constexpr double aperture = 0.0;

	std::ofstream file(std::string(argv[1]) + ".ppm");

	file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	Camera cam{ lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus };
	double R = cos(pi / 4);

	HittableList world = two_perlin_spheres();

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