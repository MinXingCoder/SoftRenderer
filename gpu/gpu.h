#pragma once
#include "framebuffer.h"

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
	void drawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, const RGBA& color);

private:
	void drawLineImpl(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, const RGBA& color, bool flag);

	static GPU* mInstance;
	FrameBuffer* mFrameBuffer{ nullptr };
};