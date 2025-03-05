#pragma once
#include "../global/base.h"
#include <string>

class Image
{
public:
	Image(const uint32_t& width, const uint32_t& height, const RGBA* data);
	~Image();

	static Image* createImage(const std::string& path);
	static void destroy(const Image* image);

public:
	uint32_t mWidth{ 0 };
	uint32_t mHeight{ 0 };
	RGBA* mData{ nullptr };
};