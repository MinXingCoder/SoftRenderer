#pragma once

#define PI 3.1415926
#define DEG2RAD(theta) (theta * 0.01745329251994)
#define FRACTION(x) (x-(int)x)

using byte = unsigned char;

struct RGBA
{
	byte mB;
	byte mG;
	byte mR;
	byte mA;

	RGBA(byte r = 255, byte g = 255, byte b = 255, byte a = 255)
		: mB(b)
		, mG(g)
		, mR(r)
		, mA(a)
	{}
};