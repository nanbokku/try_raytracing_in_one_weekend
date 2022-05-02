#include "ConstantMedium.h"

bool ConstantMedium::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	// デバッグ中には低い確率でサンプルの様子を出力する
	// enableDebugをtrueにすると有向化。
	constexpr bool enableDebug = false;
	constexpr bool debugging = enableDebug && random_double() < 0.00001;

	HitRecord rec1, rec2;

	if (!boundary->hit(r, -infinity, infinity, rec1))	// レイの進む方向が後方でもヒットすればOK
	{
		return false;
	}

	if (!boundary->hit(r, rec1.t + 0.0001, infinity, rec2))	// 媒質の中にレイの始点がある場合を除く
	{
		return false;
	}

	if (debugging)
	{
		std::cerr << "\nt0=" << rec1.t << ", t1=" << rec2.t << std::endl;
	}

	if (rec1.t < t_min)	// 必ずrec1がrec2より手前にある
	{
		rec1.t = t_min;
	}

	if (rec2.t > t_max)
	{
		rec2.t = t_max;
	}

	if (rec1.t >= rec2.t)	// 必ずrec1がrec2より手前にある
	{
		return false;
	}

	if (rec1.t < 0)
	{
		rec1.t = 0;
	}

	const auto ray_length = r.direction().length();
	const auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;	// 境界に入ってから抜け出すまでの直線距離
	const auto hit_distance = neg_inv_density * log(random_double());	// レイが散乱するまでのランダムな長さ -1/C * log(1 - random)

	if (hit_distance > distance_inside_boundary)	// 境界の外に出た
	{
		return false;
	}

	rec.t = rec1.t + hit_distance / ray_length;	// hit_distanceだけでt*b.length()の計算を含んでいるため、ray_lengthで割る
	rec.p = r.at(rec.t);

	if (debugging)
	{
		std::cerr << "hit_distance = " << hit_distance << std::endl << "rec.t = " << rec.t << std::endl << "rec.p = " << rec.p << std::endl;
	}

	rec.normal = Vec3(1, 0, 0);	// どんな値でもよい
	rec.front_face = true;		// どんな値でもよい
	rec.mat_ptr = phase_function;

	return true;
}