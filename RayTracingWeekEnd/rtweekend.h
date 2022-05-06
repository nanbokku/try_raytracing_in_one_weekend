#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>


// 定数
constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// ユーティリティ関数
inline double degrees_to_radians(double degrees)
{
	return degrees * pi / 180;
}

inline double random_double(double min, double max)
{
	static std::random_device rd;
	static std::mt19937 generator(rd());
	std::uniform_real_distribution<double> distribution(min, max);

	return distribution(generator);
}

inline double random_double()
{
	return random_double(0.0, 1.0);
}

inline int random_int(int min, int max)
{
	return min + rand() % (max - min + 1);
}

inline double clamp(double x, double min, double max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

// 共通ヘッダー
#include "Ray.h"
#include "Vec3.h"