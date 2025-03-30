#pragma once
#include "dataStructures.h"
#include "framebuffer.h"
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

	void setBilinear(bool enable);

	void setTexture(Image* image);

	void setTextureWrap(uint32_t wrap);

private:
	RGBA sampleNearest(const math::vec2f& uv);
	RGBA sampleBilinear(const math::vec2f& uv);
	void checkWrap(float& n);

private:

	static GPU* mInstance;
	FrameBuffer* mFrameBuffer{ nullptr };
	uint32_t mWrap{ TEXTURE_WRAP_REPEAT };
	bool mEnableBlending{ false };
	bool mEnableBilinear{ false };

	Image* mImage{ nullptr };
};