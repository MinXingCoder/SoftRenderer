#include "raster.h"
#include "../math/math.h"

Raster::Raster()
{}

Raster::~Raster()
{}

void Raster::rasterizeLine(std::vector<Point>& results, const Point& v0, const Point& v1)
{
	Point start = v0, end = v1;
	if (v0.x > v1.x)
	{
		start = v1;
		end = v0;
	}

	results.emplace_back(start);

	bool flipY = false;
	if (start.y > end.y)
	{
		start.y *= -1;
		end.y *= -1;
		flipY = true;
	}

	int deltaX = static_cast<int>(end.x - start.x);
	int deltaY = static_cast<int>(end.y - start.y);
	bool swapXY = false;

	if (deltaY > deltaX)
	{
		std::swap(start.x, start.y);
		std::swap(end.x, end.y);
		swapXY = true;
	}

	deltaX = static_cast<int>(end.x - start.x);
	deltaY = static_cast<int>(end.y - start.y);
	int p = 2 * deltaY - deltaX;

	Point currentPoint{ start.x, start.y }, resultPoint;
	int resultX = 0, resultY = 0;
	for (int x = 1; x < deltaX; ++x)
	{
		currentPoint.x = x + start.x;
		if (p >= 0)
		{
			currentPoint.y += 1;
			p = p - 2 * deltaX;
		}

		p = p + 2 * deltaY;

		resultX = currentPoint.x, resultY = currentPoint.y;
		if (swapXY) std::swap(resultX, resultY);
		if (flipY) resultY *= -1;
		
		resultPoint.x = resultX, resultPoint.y = resultY;
		results.emplace_back(resultPoint);
	}
}

void Raster::interpolantLine(const Point& v0, const Point& v1, Point& target)
{
	int deltaX = v1.x - v0.x;
	float weight = 0.0f;
	if (deltaX == 0) {
		int deltaY = v1.y - v0.y;
		weight = static_cast<float>(target.y - v0.y) / deltaY;
	}
	else {
		weight = static_cast<float>(target.x - v0.x) / deltaX;
	}

	target.color = lerpRGBA(v0.color, v1.color, weight);
}

void Raster::rasterizeTriangle(std::vector<Point>& results, const Point& v0, const Point& v1, const Point& v2)
{
	int32_t maxX = std::max(v0.x, std::max(v1.x, v2.x));
	int32_t minX = std::min(v0.x, std::min(v1.x, v2.x));
	int32_t maxY = std::max(v0.y, std::max(v1.y, v2.y));
	int32_t minY = std::min(v0.y, std::min(v1.y, v2.y));

	for (int32_t i = minX; i <= maxX; ++i)
	{
		for (int32_t j = minY; j <= maxY; ++j)
		{
			math::vec2i p0(v0.x - i, v0.y - j), p1(v1.x - i, v1.y - j), p2(v2.x - i, v2.y - j);

			float r0 = math::cross(p0, p1);
			float r1 = math::cross(p1, p2);
			float r2 = math::cross(p2, p0);

			bool bNegative = (r0 < 0) && (r1 < 0) && (r2 < 0);
			bool bPositive = (r0 > 0) && (r1 > 0) && (r2 > 0);

			Point tmp;
			if (bNegative || bPositive)
			{
				tmp.x = i, tmp.y = j, tmp.color = RGBA();
				interpolantTriangle(v0, v1, v2, tmp);
				results.emplace_back(tmp);
			}
		}
	}
}

void Raster::interpolantTriangle(const Point& v0, const Point& v1, const Point& v2, Point& target)
{
	math::vec2f ab(v1.x - v0.x, v1.y - v0.y), ac(v2.x - v0.x, v2.y - v0.y);
	float abc = std::abs(math::cross(ab, ac));
	math::vec2f pb(v1.x - target.x, v1.y - target.y), pc(v2.x - target.x, v2.y - target.y);
	float bpc = std::abs(math::cross(pb, pc));
	float alpha = bpc / abc;

	math::vec2f pa(v0.x - target.x, v0.y - target.y);
	float apc = std::abs(math::cross(pa, pc));
	float beta = apc / abc;

	float apb = std::abs(math::cross(pa, pb));
	float gamma = apb / abc;

	target.color = lerpRGBA(v0.color, v1.color, v2.color, alpha, beta, gamma);
	target.uv = lerpUV(v0.uv, v1.uv, v2.uv, alpha, beta, gamma);
}

RGBA Raster::lerpRGBA(const RGBA& c0, const RGBA& c1, float weight)
{
	RGBA value;
	value.mR = c1.mR * weight + c0.mR * (1 - weight);
	value.mG = c1.mG * weight + c0.mG * (1 - weight);
	value.mB = c1.mB * weight + c0.mB * (1 - weight);
	value.mA = c1.mA * weight + c0.mA * (1 - weight);
	return value;
}

RGBA Raster::lerpRGBA(const RGBA& c0, const RGBA& c1, const RGBA& c2, float weight0, float weight1, float weight2)
{
	RGBA value;
	value.mR = c0.mR * weight0 + c1.mR * weight1 + c2.mR * weight2;
	value.mG = c0.mG * weight0 + c1.mG * weight1 + c2.mG * weight2;
	value.mB = c0.mB * weight0 + c1.mB * weight1 + c2.mB * weight2;
	value.mA = c0.mA * weight0 + c1.mA * weight1 + c2.mA * weight2;

	return value;
}

math::vec2f Raster::lerpUV(const math::vec2f& uv0, const math::vec2f& uv1, const math::vec2f& uv2, float weight0, float weight1, float weight2)
{
	math::vec2f value = uv0 * weight0 + uv1 * weight1 + uv2 * weight2;
	return value;
}