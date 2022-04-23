#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>


// 定数
constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// ユーティリティ関数
inline double degrees_to_radians(double degrees)
{
	return degrees * pi / 180;
}

// 共通ヘッダー
#include "Ray.h"
#include "Vec3.h"