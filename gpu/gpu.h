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

private:
	static GPU* mInstance;
	FrameBuffer* mFrameBuffer{ nullptr };
};