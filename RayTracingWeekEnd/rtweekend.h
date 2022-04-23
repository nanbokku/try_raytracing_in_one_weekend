#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>


// �萔
constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// ���[�e�B���e�B�֐�
inline double degrees_to_radians(double degrees)
{
	return degrees * pi / 180;
}

// ���ʃw�b�_�[
#include "Ray.h"
#include "Vec3.h"