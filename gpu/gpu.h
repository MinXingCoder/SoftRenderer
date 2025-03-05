#pragma once
#include "framebuffer.h"
#include "../global/base.h"
#include "../application/image.h"

#define sgl GPU::getInstance()

class GPU
{
public:
	static GPU* getInstance();
	
	GPU();
	~GPU();

	void initSurface(const uint32_t& width, const uint32_t& height, void* buffer);
	void clear();
	void drawPoint(uint32_t x, uint32_t y, const RGBA& color);
	void drawLine(const Point& v0, const Point& v1);
	void drawTriangle(const Point& p1, const Point& p2, const Point& p3);
	void drawImage(const Image* image);
	void drawImageWithAlpha(const Image* image, const uint32_t& alpha);

	void setBlending(bool enable);

	void setTexture(Image* image);

private:
	RGBA sampleNearest(const math::vec2f& uv);

private:

	static GPU* mInstance;
	FrameBuffer* mFrameBuffer{ nullptr };
	bool mEnableBlending{ false };

	Image* mImage{ nullptr };
};