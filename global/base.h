//
// Created by scc on 2025/11/2.
//
#pragma once
#include <stdint.h>

#define DEG2RAD(theta)		(0.01745329251994329 * (theta))

using byte = uint8_t;

struct RGBA
{
    byte R;
    byte G;
    byte B;
    byte A;
};

struct Point
{
    int x;
    int y;
    RGBA color;
};