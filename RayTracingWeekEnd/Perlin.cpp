#include "Perlin.h"

inline double trilinear_interp(Vec3 c[2][2][2], double u, double v, double w)
{
	// herimite interpolation
	auto uu = u * u * (3 - 2 * u);
	auto vv = v * v * (3 - 2 * v);
	auto ww = w * w * (3 - 2 * w);
	auto accum = 0.0;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				Vec3 weight_v(u - i, v - j, w - k);
				accum += (i * uu + (1 - i) * (1 - uu)) * (j * vv + (1 - j) * (1 - vv)) * (k * ww + (1 - k) * (1 - ww)) * dot(c[i][j][k], weight_v);
			}
		}
	}

	return accum;	// [-1,1]
}

Perlin::Perlin()
{
	ranvec = new Vec3[point_count];
	for (int i = 0; i < point_count; i++)
	{
		ranvec[i] = unit_vector(Vec3::random(-1, 1));
	}

	perm_x = perlin_generate_perm();
	perm_y = perlin_generate_perm();
	perm_z = perlin_generate_perm();
}

Perlin::~Perlin()
{
	delete[] perm_x;
	delete[] perm_y;
	delete[] perm_z;
	delete[] ranvec;
}

double Perlin::noise(const Point3& p) const
{
	auto u = p.x() - floor(p.x());	//frac()?
	auto v = p.y() - floor(p.y());
	auto w = p.z() - floor(p.z());
	int i = floor(p.x());
	int j = floor(p.y());
	int k = floor(p.z());
	Vec3 c[2][2][2];

	for (int di = 0; di < 2; di++)
	{
		for (int dj = 0; dj < 2; dj++)
		{
			for (int dk = 0; dk < 2; dk++)
			{
				// 3次元のボックスを作った後trilinear補間
				c[di][dj][dk] = ranvec[
					perm_x[(i + di) & (point_count - 1)] ^
						perm_y[(j + dj) & (point_count - 1)] ^
						perm_z[(k + dk) & (point_count - 1)]
				];
			}
		}
	}

	return trilinear_interp(c, u, v, w);
}

double Perlin::turb(const Point3& p, int depth) const
{
	double accum = 0.0;
	Point3 temp_p = p;
	double weight = 1.0;

	for (int i = 0; i < depth; i++)
	{
		accum += weight * noise(temp_p);
		weight *= 0.5;
		temp_p *= 2;
	}

	return fabs(accum);
}

int* Perlin::perlin_generate_perm()
{
	auto p = new int[point_count];

	for (int i = 0; i < Perlin::point_count; i++)
	{
		p[i] = i;
	}

	// ランダムに並び替える
	permute(p, point_count);

	return p;
}

void Perlin::permute(int* p, int n)
{
	for (int i = n - 1; i > 0; i--)
	{
		int target = random_int(0, i);
		std::swap(p[i], p[target]);
	}
}