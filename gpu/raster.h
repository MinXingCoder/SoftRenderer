#pragma once
#include "base.h"
#include <vector>

class Raster
{
public:
	Raster();
	~Raster();
	
	static void rasterizeLine(std::vector<Point>& results, const Point& v0, const Point& v1);
	static void interpolantLine(const Point& v0, const Point& v1, Point& target);
	static void rasterizeTriangle(std::vector<Point>& results, const Point& v0, const Point& v1, const Point& v2);
};