#pragma once
#include "../math/math.h"

struct BindingDescription
{
	uint32_t mVboId{ 0 };
	size_t mItemSize{ 0 };
	size_t mStride{ 0 };
	size_t mOffset{ 0 };
};

struct VsOutput
{
	math::vec4f mPosition{ 0.0f, 0.0f, 0.0f, 1.0f };
	math::vec4f mColor;		// 0.0f ~ 1.0f
	math::vec2f mUV;
};

struct FsOutput
{
	math::vec2i mPixelPos;
	float mDepth;
	RGBA mColor;					// 0 ~ 255
};