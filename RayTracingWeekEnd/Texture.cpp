#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

ImageTexture::ImageTexture(const char* filename)
{
	auto components_per_pixel = bytes_per_pixel;

	data = stbi_load(filename, &width, &height, &components_per_pixel, components_per_pixel);

	if (!data)
	{
		std::cerr << "ERROR: Could not load texture image file '" << filename << "'." << std::endl;
		
		width = height = 0;
	}

	bytes_per_scanline = bytes_per_pixel * width;
}

Color ImageTexture::value(double u, double v, const Vec3& p) const
{
	// �e�N�X�`���̃f�[�^���Ȃ����ɂ́A���̂��Ƃ�������悤�ɃV�A���F��Ԃ�
	if (data == nullptr)
	{
		return Color(0, 1, 1);
	}

	// ���͂��ꂽ�e�N�X�`�����W��[0,1]�Ő؂�̂Ă�
	u = clamp(u, 0.0, 1.0);
	v = 1.0 - clamp(v, 0.0, 1.0);	// v�𔽓]�����ĉ摜�̍��W�n�ɍ��킹��

	auto i = static_cast<int>(u * width);
	auto j = static_cast<int>(v * height);

	// �������W������ɐ؂�̂āi�e�N�X�`�����W��1.0�ɂȂ��Ă͂����Ȃ��j
	if (i >= width) i = width - 1;
	if (j >= height) j = height - 1;

	const auto color_scale = 1.0 / 255.0;
	auto pixel = data + j * bytes_per_scanline + i * bytes_per_pixel;

	return Color(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
}