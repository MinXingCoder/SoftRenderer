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