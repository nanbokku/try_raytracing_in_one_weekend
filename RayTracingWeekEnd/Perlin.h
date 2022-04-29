#pragma once

#include "rtweekend.h"

class Perlin
{
public:
	Perlin();
	~Perlin();

	double noise(const Point3& p) const;
	double turb(const Point3& p, int depth = 7) const;

private:
	static int* perlin_generate_perm();
	static void permute(int* p, int n);

	static constexpr int point_count = 256;
	int* perm_x;
	int* perm_y;
	int* perm_z;
	Vec3* ranvec;
};

