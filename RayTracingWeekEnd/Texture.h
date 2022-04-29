#pragma once

#include "rtweekend.h"
#include "Perlin.h"

class Texture
{
public:
	virtual ~Texture() = default;

	virtual Color value(double u, double v, const Point3& p) const = 0;
};

class SolidColor : public Texture
{
public:
	SolidColor() = default;
	SolidColor(Color c)
		:color_value(c)
	{
	}

	SolidColor(double red, double green, double blue)
		: SolidColor(Color(red, green, blue))
	{
	}

	virtual Color value(double u, double v, const Point3& p) const
	{
		return color_value;
	}

private:
	Color color_value{};
};

class CheckerTexture : public Texture
{
public:
	CheckerTexture() = default;
	CheckerTexture(const std::shared_ptr<Texture>& t0, const std::shared_ptr<Texture>& t1)
		:even(t0), odd(t1)
	{
	}

	virtual Color value(double u, double v, const Point3& p) const
	{
		auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());

		if (sines < 0)
		{
			return odd->value(u, v, p);
		}
		else
		{
			return even->value(u, v, p);
		}
	}

private:
	std::shared_ptr<Texture> even;
	std::shared_ptr<Texture> odd;
};

class NoiseTexture : public Texture
{
public:
	NoiseTexture() = default;
	NoiseTexture(double sc)
		:scale(sc)
	{
	}

	virtual Color value(double u, double v, const Point3& p) const
	{
		//return Color(1, 1, 1) * 0.5 * (1.0 + noise.noise(scale * p));	// noise()の出力が[-1,1]なので[0,1]に補正
		//return Color(1, 1, 1) * noise.turb(scale * p);	// 乱流ノイズ
		return Color(1, 1, 1) * 0.5 * (1.0 + sin(scale * p.z() + 10 * noise.turb(p)));	// 大理石ノイズ
	}

private:
	Perlin noise{};
	double scale{};
};