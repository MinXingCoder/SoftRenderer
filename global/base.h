#pragma once
#include <stdint.h>
#include "../math/math.h"

#define PI 3.1415926
#define DEG2RAD(theta) (theta * 0.01745329251994)
#define FRACTION(x) (x-(int)x)
#define STATIC_ASSERT(condition) static_assert(condition, #condition)

using byte = unsigned char;

struct RGBA
{
	byte mB;
	byte mG;
	byte mR;
	byte mA;

	// a 255 完全不透明
	RGBA(byte r = 255, byte g = 255, byte b = 255, byte a = 255)
		: mB(b)
		, mG(g)
		, mR(r)
		, mA(a)
	{}
};

struct Point
{
	int32_t x;
	int32_t y;
	RGBA color;
	math::vec2f uv;
};

#define TEXTURE_WRAP_REPEAT 0
#define TEXTURE_WRAP_MIRROR 1