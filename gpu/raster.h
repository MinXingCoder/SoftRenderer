//
// Created by scc on 2025/11/2.
//
#pragma once
#include <vector>
#include "../global/base.h"

class Raster
{
public:
    static void rasterizeLine(const Point& start, const Point& end, std::vector<Point>& results);
};