#include <iostream>
#include <fstream>

#include "Color.h"

int main()
{
	constexpr int image_width = 256;
	constexpr int image_height = 256;

	std::ofstream file("image.ppm");

	file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

		for (int i = 0; i < image_width; ++i)
		{
			Color pixel_color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
			write_color(file, pixel_color);
		}
	}

	std::cerr << "\nDone.\n";

	return 0;
}