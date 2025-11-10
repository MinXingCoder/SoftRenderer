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
    static void rasterTriangle(const Point& p0, const Point& p1, const Point& p2, std::vector<Point>& results);

    static void interpolantLine(const Point& start, const Point& end, Point& target);
    static void interpolantTriangle(const Point& p0, const Point& p1, const Point& p2, Point& target);
};