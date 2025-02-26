#include "gpu.h"
#include <string.h>
#include <algorithm>
#include "raster.h"

GPU* GPU::mInstance = nullptr;

GPU* GPU::getInstance()
{
	if (mInstance == nullptr)
	{
		static GPU gpu;
		mInstance = &gpu;
	}

	return mInstance;
}

GPU::GPU()
{}

GPU::~GPU()
{
	if (mFrameBuffer)
	{
		delete mFrameBuffer;
	}
}

void GPU::initSurface(const uint32_t& width, const uint32_t& height, void* buffer)
{
	mFrameBuffer = new FrameBuffer(width, height, buffer);
}

void GPU::clear()
{
	size_t pixelSize = mFrameBuffer->mWidth * mFrameBuffer->mHeight;
	std::fill_n(mFrameBuffer->mColorBuffer, pixelSize, RGBA(0, 0, 0, 0));
}

void GPU::drawPoint(uint32_t x, uint32_t y, const RGBA& color)
{
	if (x >= mFrameBuffer->mWidth || y >= mFrameBuffer->mHeight) return;
	uint32_t pixelPos = x + y * mFrameBuffer->mWidth;
	mFrameBuffer->mColorBuffer[pixelPos] = color;
}

void GPU::drawLine(const Point& v0, const Point& v1)
{
	std::vector<Point> pixels;

	Raster::rasterizeLine(pixels, v0, v1);

	for (auto& item : pixels)
	{
		Raster::interpolantLine(v0, v1, item);
		drawPoint(item.x, item.y, item.color);
	}
}

void GPU::drawTriangle(const Point& p1, const Point& p2, const Point& p3)
{
	std::vector<Point> pixels;

	Raster::rasterizeTriangle(pixels, p1, p2, p3);

	for (auto& item : pixels)
	{
		drawPoint(item.x, item.y, item.color);
	}
}