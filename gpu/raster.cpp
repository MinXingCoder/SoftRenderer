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

	target.color.mR = v0.color.mR * (1 - weight) + v1.color.mR * weight;
	target.color.mG = v0.color.mG * (1 - weight) + v1.color.mG * weight;
	target.color.mB = v0.color.mB * (1 - weight) + v1.color.mB * weight;
	target.color.mA = v0.color.mA * (1 - weight) + v1.color.mA * weight;
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
				results.emplace_back(tmp);
			}
		}
	}
}