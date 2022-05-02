#include "ConstantMedium.h"

bool ConstantMedium::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	// �f�o�b�O���ɂ͒Ⴂ�m���ŃT���v���̗l�q���o�͂���
	// enableDebug��true�ɂ���ƗL�����B
	constexpr bool enableDebug = false;
	constexpr bool debugging = enableDebug && random_double() < 0.00001;

	HitRecord rec1, rec2;

	if (!boundary->hit(r, -infinity, infinity, rec1))	// ���C�̐i�ޕ���������ł��q�b�g�����OK
	{
		return false;
	}

	if (!boundary->hit(r, rec1.t + 0.0001, infinity, rec2))	// �}���̒��Ƀ��C�̎n�_������ꍇ������
	{
		return false;
	}

	if (debugging)
	{
		std::cerr << "\nt0=" << rec1.t << ", t1=" << rec2.t << std::endl;
	}

	if (rec1.t < t_min)	// �K��rec1��rec2����O�ɂ���
	{
		rec1.t = t_min;
	}

	if (rec2.t > t_max)
	{
		rec2.t = t_max;
	}

	if (rec1.t >= rec2.t)	// �K��rec1��rec2����O�ɂ���
	{
		return false;
	}

	if (rec1.t < 0)
	{
		rec1.t = 0;
	}

	const auto ray_length = r.direction().length();
	const auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;	// ���E�ɓ����Ă��甲���o���܂ł̒�������
	const auto hit_distance = neg_inv_density * log(random_double());	// ���C���U������܂ł̃����_���Ȓ��� -1/C * log(1 - random)

	if (hit_distance > distance_inside_boundary)	// ���E�̊O�ɏo��
	{
		return false;
	}

	rec.t = rec1.t + hit_distance / ray_length;	// hit_distance������t*b.length()�̌v�Z���܂�ł��邽�߁Aray_length�Ŋ���
	rec.p = r.at(rec.t);

	if (debugging)
	{
		std::cerr << "hit_distance = " << hit_distance << std::endl << "rec.t = " << rec.t << std::endl << "rec.p = " << rec.p << std::endl;
	}

	rec.normal = Vec3(1, 0, 0);	// �ǂ�Ȓl�ł��悢
	rec.front_face = true;		// �ǂ�Ȓl�ł��悢
	rec.mat_ptr = phase_function;

	return true;
}