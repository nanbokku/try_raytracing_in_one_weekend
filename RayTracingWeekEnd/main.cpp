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
#include "DiffuseLight.h"
#include "XYRect.h"
#include "YZRect.h"
#include "XZRect.h"
#include "BVHNode.h"
#include "Box.h"
#include "ConstantMedium.h"


Color ray_color(const Ray& r, const Color& background, const Hittable& world, int depth)
{
	HitRecord rec{};

	// 反射回数が一定よりも多くなったら、その時点で追跡をやめる
	if (depth <= 0)
	{
		return Color(0, 0, 0);
	}

	if (!world.hit(r, 0.001, infinity, rec))
	{
		// レイがどのオブジェクトとも交わらないなら背景色を返す
		return background;
	}

	Ray scattered;
	Color attenuation;
	Color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

	if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
	{
		// レイが反射しないとき
		return emitted;
	}


	return emitted + attenuation * ray_color(scattered, background, world, depth - 1);
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

HittableList earth()
{
	auto earth_texture = std::make_shared<ImageTexture>("world.jpg");
	auto earth_surface = std::make_shared<Lambertian>(earth_texture);
	auto globe = std::make_shared<Sphere>(Point3(0, 0, 0), 2, earth_surface);
	return HittableList(globe);
}

HittableList simple_light()
{
	HittableList objects{};

	auto pertext = std::make_shared<NoiseTexture>(4);
	objects.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, std::make_shared<Lambertian>(pertext)));
	objects.add(std::make_shared<Sphere>(Point3(0, 2, 0), 2, std::make_shared<Lambertian>(pertext)));

	auto difflight = std::make_shared<DiffuseLight>(std::make_shared<SolidColor>(4, 4, 4));
	objects.add(std::make_shared<Sphere>(Point3(0, 7, 0), 2, difflight));
	objects.add(std::make_shared<XYRect>(3, 5, 1, 3, -2, difflight));

	return objects;
}

HittableList cornell_box()
{
	HittableList objects{};

	auto red = std::make_shared<Lambertian>(std::make_shared<SolidColor>(.65, .05, .05));
	auto white = std::make_shared<Lambertian>(std::make_shared<SolidColor>(.73, .73, .73));
	auto green = std::make_shared<Lambertian>(std::make_shared<SolidColor>(.12, .45, .15));
	auto light = std::make_shared<DiffuseLight>(std::make_shared<SolidColor>(1, 1, 1));

	objects.add(std::make_shared<YZRect>(0, 555, 0, 555, 555, green));
	objects.add(std::make_shared<YZRect>(0, 555, 0, 555, 0, red));
	objects.add(std::make_shared<XZRect>(213, 343, 227, 332, 554, light));
	objects.add(std::make_shared<XZRect>(0, 555, 0, 555, 555, white));
	objects.add(std::make_shared<XZRect>(0, 555, 0, 555, 0, white));
	objects.add(std::make_shared<XYRect>(0, 555, 0, 555, 555, white));

	std::shared_ptr<Hittable> box1 = std::make_shared<Box>(Point3(0, 0, 0), Point3(165, 330, 165), white);
	box1 = std::make_shared<RotateY>(box1, 15);
	box1 = std::make_shared<Translate>(box1, Vec3(265, 0, 295));
	objects.add(box1);

	std::shared_ptr<Hittable> box2 = std::make_shared<Box>(Point3(0, 0, 0), Point3(165, 165, 165), white);
	box2 = std::make_shared<RotateY>(box2, -18);
	box2 = std::make_shared<Translate>(box2, Vec3(130, 0, 65));
	objects.add(box2);

	return objects;
}

HittableList cornell_smoke()
{
	HittableList objects{};

	auto red = std::make_shared<Lambertian>(std::make_shared<SolidColor>(.65, .05, .05));
	auto white = std::make_shared<Lambertian>(std::make_shared<SolidColor>(.73, .73, .73));
	auto green = std::make_shared<Lambertian>(std::make_shared<SolidColor>(.12, .45, .15));
	auto light = std::make_shared<DiffuseLight>(std::make_shared<SolidColor>(7, 7, 7));

	objects.add(std::make_shared<YZRect>(0, 555, 0, 555, 555, green));
	objects.add(std::make_shared<YZRect>(0, 555, 0, 555, 0, red));
	objects.add(std::make_shared<XZRect>(113, 443, 127, 432, 554, light));
	objects.add(std::make_shared<XZRect>(0, 555, 0, 555, 555, white));
	objects.add(std::make_shared<XZRect>(0, 555, 0, 555, 0, white));
	objects.add(std::make_shared<XYRect>(0, 555, 0, 555, 555, white));

	std::shared_ptr<Hittable> box1 = std::make_shared<Box>(Point3(0, 0, 0), Point3(165, 330, 165), white);
	box1 = std::make_shared<RotateY>(box1, 15);
	box1 = std::make_shared<Translate>(box1, Vec3(265, 0, 295));

	std::shared_ptr<Hittable> box2 = std::make_shared<Box>(Point3(0, 0, 0), Point3(165, 165, 165), white);
	box2 = std::make_shared<RotateY>(box2, -18);
	box2 = std::make_shared<Translate>(box2, Vec3(130, 0, 65));

	objects.add(std::make_shared<ConstantMedium>(box1, 0.01, std::make_shared<SolidColor>(0, 0, 0)));
	objects.add(std::make_shared<ConstantMedium>(box2, 0.01, std::make_shared<SolidColor>(1, 1, 1)));

	return objects;
}


int main(int argc, char* argv[])
{
	constexpr double aspect_ratio = 1.0;
	constexpr int image_width = 500;
	constexpr int image_height = static_cast<int>(image_width / aspect_ratio);
	constexpr int samples_per_pixel = 100;
	constexpr int max_depth = 50;
	const Point3 lookfrom{ 278, 278, -800 };
	const Point3 lookat{ 278,278,0 };
	const Vec3 vup{ 0,1,0 };
	const double dist_to_focus = 10;
	constexpr double aperture = 0.0;
	constexpr double vfov = 40.0;
	const Color background_color{ 0,0,0 };

	//std::ofstream file(std::string(argv[1]) + ".ppm");

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	Camera cam{ lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus };
	double R = cos(pi / 4);

	HittableList world = cornell_smoke();
	auto bvh = BVHNode(world, 0.001, infinity);

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

				pixel_color += ray_color(ray, background_color, bvh, max_depth);
			}

			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}

	std::cerr << "\nDone.\n";

	return 0;
}