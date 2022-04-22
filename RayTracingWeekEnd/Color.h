#pragma once

#include "Vec3.h"
#include <iostream>
#include <fstream>

void write_color(std::ostream& out, const Color& pixel_color)
{
	// Še¬•ª‚ğ[0,255]‚É•ÏŠ·‚µ‚Äo—Í
	out << static_cast<int>(255.999 * pixel_color.x()) << ' ' << static_cast<int>(255.999 * pixel_color.y()) << ' ' << static_cast<int>(255.999 * pixel_color.z()) << std::endl;
}

void write_color(std::ofstream& out, const Color& pixel_color)
{
	out << static_cast<int>(255.999 * pixel_color.x()) << ' ' << static_cast<int>(255.999 * pixel_color.y()) << ' ' << static_cast<int>(255.999 * pixel_color.z()) << std::endl;
}