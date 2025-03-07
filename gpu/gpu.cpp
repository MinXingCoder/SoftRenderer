#include "gpu.h"
#include <string.h>
#include <algorithm>
#include "raster.h"
#include <cmath>

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

	RGBA result = color;

	if (mEnableBlending)
	{
		float weight = color.mA / 255.0f;
		auto dst = mFrameBuffer->mColorBuffer[pixelPos];
		result.mR = result.mR * weight + dst.mR * (1 - weight);
		result.mG = result.mG * weight + dst.mG * (1 - weight);
		result.mB = result.mB * weight + dst.mB * (1 - weight);
		result.mA = result.mA * weight + dst.mA * (1 - weight);
	}

	mFrameBuffer->mColorBuffer[pixelPos] = result;
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
		if (mImage)
		{
			RGBA result;
			if (mEnableBilinear)
				result = sampleBilinear(item.uv);
			else 
				result = sampleNearest(item.uv);
			drawPoint(item.x, item.y, result);
		}
		else {
			drawPoint(item.x, item.y, item.color);
		}
	}
}

void GPU::drawImage(const Image* image)
{
	for (uint32_t i = 0; i < image->mWidth; ++i)
	{
		for (uint32_t j = 0; j < image->mHeight; ++j)
		{
			drawPoint(i, j, image->mData[j * image->mWidth + i]);
		}
	}
}

void GPU::drawImageWithAlpha(const Image* image, const uint32_t& alpha)
{
	for (uint32_t i = 0; i < image->mWidth; ++i)
	{
		for (uint32_t j = 0; j < image->mHeight; ++j)
		{
			image->mData[j * image->mWidth + i].mA = alpha;
			drawPoint(i, j, image->mData[j * image->mWidth + i]);
		}
	}
}

void GPU::setBlending(bool enable)
{
	mEnableBlending = enable;
}

void GPU::setBilinear(bool enable)
{
	mEnableBilinear = enable;
}

void GPU::setTexture(Image* image)
{
	mImage = image;
}

void GPU::setTextureWrap(uint32_t wrap)
{
	mWrap = wrap;
}

RGBA GPU::sampleNearest(const math::vec2f& uv)
{
	math::vec2f tmpUV = uv;
	checkWrap(tmpUV.x);
	checkWrap(tmpUV.y);

	int x = std::round(tmpUV.x * (mImage->mWidth - 1));
	int y = std::round(tmpUV.y * (mImage->mHeight - 1));

	return mImage->mData[y * mImage->mWidth + x];
}

RGBA GPU::sampleBilinear(const math::vec2f& uv)
{
	math::vec2f tmpUV = uv;
	checkWrap(tmpUV.x);
	checkWrap(tmpUV.y);

	float x = tmpUV.x * (mImage->mWidth - 1);
	float y = tmpUV.y * (mImage->mHeight - 1);

	int left = std::floor(x);
	int right = std::ceil(x);
	int bottom = std::floor(y);
	int top = std::floor(y);

	int leftBottomPosition = left + bottom * mImage->mWidth;
	int leftTopPosition = left + top * mImage->mWidth;
	int rightBottomPosition = right + bottom * mImage->mWidth;
	int rightTopPosition = right + top * mImage->mWidth;

	RGBA leftBottomColor = mImage->mData[leftBottomPosition];
	RGBA leftTopColor = mImage->mData[leftTopPosition];
	RGBA rightBottomColor = mImage->mData[rightBottomPosition];
	RGBA rightTopColor = mImage->mData[rightTopPosition];

	float yWeight{};
	if (bottom == top)
	{
		yWeight = 1.0f;
	}
	else {
		yWeight = (top - y) / (top - bottom);
	}

	RGBA leftColor = Raster::lerpRGBA(leftTopColor, leftBottomColor, yWeight);
	RGBA rightColor = Raster::lerpRGBA(rightTopColor, rightBottomColor, yWeight);

	float xWeight{};
	if (left == right)
	{
		xWeight = 1.0f;
	}
	else {
		xWeight = (right - x) / (right - left);
	}

	RGBA returnColor = Raster::lerpRGBA(rightColor, leftColor, xWeight);
	return returnColor;
}

void GPU::checkWrap(float& n)
{
	if (n > 1.0f || n < 0.0f)
	{
		switch (mWrap)
		{
		case TEXTURE_WRAP_REPEAT:
		{
			n = FRACTION(1 + FRACTION(n));
			break;
		}
		case TEXTURE_WRAP_MIRROR:
		{
			n = 1 - FRACTION(1 + FRACTION(n));
			break;
		}
		default:
			break;
		}
	}
}