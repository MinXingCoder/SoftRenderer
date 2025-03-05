#pragma once
#include "../global/base.h"
#include <stdint.h>

class FrameBuffer
{
public:
	FrameBuffer(uint32_t width, uint32_t height, void* buffer);
	~FrameBuffer();

	FrameBuffer(const FrameBuffer&) = delete;

	uint32_t mWidth;
	uint32_t mHeight;
	RGBA* mColorBuffer;

	bool mExternBuffer;
};