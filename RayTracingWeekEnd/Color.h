#pragma once

#include "Vec3.h"
#include <iostream>
#include <fstream>


void write_color(std::ostream& out, const Color& pixel_color, int samples_per_pixel)
{
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// NaN�̂Ƃ��̓[���ɒu��
	if (isnan(r)) r = 0.0;
	if (isnan(g)) g = 0.0;
	if (isnan(b)) b = 0.0;

	// �F�̍��v���T���v���̐��Ŋ���Agamma=2.0�̃K���}�␳���s��
	double scale = 1.0 / samples_per_pixel;
	r = sqrt(r * scale);
	g = sqrt(g * scale);
	b = sqrt(b * scale);

	// �e������[0,255]�ɕϊ����ďo��
	out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' ' 
		<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' ' 
		<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << std::endl;
}