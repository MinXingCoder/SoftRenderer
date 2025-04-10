#include "raster.h"

Raster::Raster()
{}

Raster::~Raster()
{}

void Raster::rasterize(
	std::vector<VsOutput>& results,
	const uint32_t& drawMode,
	const std::vector<VsOutput>& inputs
)
{
	if (drawMode == DRAW_LINES)
	{
		for (uint32_t i = 0; i < inputs.size(); i += 2)
		{
			rasterizeLine(results, inputs[i], inputs[i + 1]);
		}
	}

	if (drawMode == DRAW_TRIANGLES)
	{
		for (uint32_t i = 0; i < inputs.size(); i += 3)
		{
			rasterizeTriangle(results, inputs[i], inputs[i + 1], inputs[i + 2]);
		}
	}
}

void Raster::rasterizeLine(std::vector<VsOutput>& results, const VsOutput& v0, const VsOutput& v1)
{
	VsOutput start = v0, end = v1;
	if (v0.mPosition.x > v1.mPosition.x)
	{
		start = v1;
		end = v0;
	}

	results.emplace_back(start);

	bool flipY = false;
	if (start.mPosition.y > end.mPosition.y)
	{
		start.mPosition.y *= -1;
		end.mPosition.y *= -1;
		flipY = true;
	}

	int deltaX = static_cast<int>(end.mPosition.x - start.mPosition.x);
	int deltaY = static_cast<int>(end.mPosition.y - start.mPosition.y);
	bool swapXY = false;

	if (deltaY > deltaX)
	{
		std::swap(start.mPosition.x, start.mPosition.y);
		std::swap(end.mPosition.x, end.mPosition.y);
		swapXY = true;
	}

	deltaX = static_cast<int>(end.mPosition.x - start.mPosition.x);
	deltaY = static_cast<int>(end.mPosition.y - start.mPosition.y);
	int p = 2 * deltaY - deltaX;

	VsOutput currentPoint{ start }, resultPoint;
	int resultX = 0, resultY = 0;
	for (int x = 1; x < deltaX; ++x)
	{
		currentPoint.mPosition.x = x + start.mPosition.x;
		if (p >= 0)
		{
			currentPoint.mPosition.y += 1;
			p = p - 2 * deltaX;
		}

		p = p + 2 * deltaY;

		resultX = currentPoint.mPosition.x, resultY = currentPoint.mPosition.y;
		if (swapXY) std::swap(resultX, resultY);
		if (flipY) resultY *= -1;
		
		resultPoint.mPosition.x = resultX, resultPoint.mPosition.y = resultY;

		interpolantLine(start, end, resultPoint);

		results.emplace_back(resultPoint);
	}
}

void Raster::interpolantLine(const VsOutput& v0, const VsOutput& v1, VsOutput& target)
{
	int deltaX = v1.mPosition.x - v0.mPosition.x;
	float weight = 0.0f;
	if (deltaX == 0) {
		int deltaY = v1.mPosition.y - v0.mPosition.y;
		weight = static_cast<float>(target.mPosition.y - v0.mPosition.y) / deltaY;
	}
	else {
		weight = static_cast<float>(target.mPosition.x - v0.mPosition.x) / deltaX;
	}

	target.mColor = math::lerp(v0.mColor, v1.mColor, weight);
	target.mUV = math::lerp(v0.mUV, v1.mUV, weight);
}

void Raster::rasterizeTriangle(std::vector<VsOutput>& results, const VsOutput& v0, const VsOutput& v1, const VsOutput& v2)
{
	int32_t maxX = std::max(v0.mPosition.x, std::max(v1.mPosition.x, v2.mPosition.x));
	int32_t minX = std::min(v0.mPosition.x, std::min(v1.mPosition.x, v2.mPosition.x));
	int32_t maxY = std::max(v0.mPosition.y, std::max(v1.mPosition.y, v2.mPosition.y));
	int32_t minY = std::min(v0.mPosition.y, std::min(v1.mPosition.y, v2.mPosition.y));

	for (int32_t i = minX; i <= maxX; ++i)
	{
		for (int32_t j = minY; j <= maxY; ++j)
		{
			math::vec2i p0(v0.mPosition.x - i, v0.mPosition.y - j), p1(v1.mPosition.x - i, v1.mPosition.y - j), p2(v2.mPosition.x - i, v2.mPosition.y - j);

			float r0 = math::cross(p0, p1);
			float r1 = math::cross(p1, p2);
			float r2 = math::cross(p2, p0);

			bool bNegative = (r0 < 0) && (r1 < 0) && (r2 < 0);
			bool bPositive = (r0 > 0) && (r1 > 0) && (r2 > 0);

			VsOutput tmp;
			if (bNegative || bPositive)
			{
				tmp.mPosition.x = i, tmp.mPosition.y = j;
				interpolantTriangle(v0, v1, v2, tmp);
				results.emplace_back(tmp);
			}
		}
	}
}

void Raster::interpolantTriangle(const VsOutput& v0, const VsOutput& v1, const VsOutput& v2, VsOutput& target)
{
	math::vec2f ab(v1.mPosition.x - v0.mPosition.x, v1.mPosition.y - v0.mPosition.y), ac(v2.mPosition.x - v0.mPosition.x, v2.mPosition.y - v0.mPosition.y);
	float abc = std::abs(math::cross(ab, ac));
	math::vec2f pb(v1.mPosition.x - target.mPosition.x, v1.mPosition.y - target.mPosition.y), pc(v2.mPosition.x - target.mPosition.x, v2.mPosition.y - target.mPosition.y);
	float bpc = std::abs(math::cross(pb, pc));
	float alpha = bpc / abc;

	math::vec2f pa(v0.mPosition.x - target.mPosition.x, v0.mPosition.y - target.mPosition.y);
	float apc = std::abs(math::cross(pa, pc));
	float beta = apc / abc;

	float apb = std::abs(math::cross(pa, pb));
	float gamma = apb / abc;

	target.mColor = math::lerp(v0.mColor, v1.mColor, v2.mColor, alpha, beta, gamma);
	target.mUV = lerp(v0.mUV, v1.mUV, v2.mUV, alpha, beta, gamma);
}