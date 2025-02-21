#include "gpu.h"
#include <string.h>
#include <algorithm>

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
	mFrameBuffer->mColorBuffer[x + y * mFrameBuffer->mWidth] = color;
}

void GPU::drawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, const RGBA& color)
{
	uint32_t deltaX = x1 - x0, deltaY = y1 - y0;
	if (deltaY > deltaX) {
		drawLineImpl(y0, x0, y1, x1, color, false);
	}
	else {
		drawLineImpl(x0, y0, x1, y1, color, true);
	}
}

void GPU::drawLineImpl(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, const RGBA& color, bool flag)
{
	uint32_t x = x0, y = y0, deltaX = x1 - x0, deltaY = y1 - y0;
	int p = 2 * deltaY - deltaX;

	while (x < x1) 
	{
		if (flag) drawPoint(x, y, color);
		else drawPoint(y, x, color);

		++x;

		if (p >= 0) 
		{
			y = y + 1;
			p = p - 2 * deltaX;
		}
		p = p + 2 * deltaY;
	}

	if (flag) drawPoint(x, y, color);
	else drawPoint(y, x, color);
}