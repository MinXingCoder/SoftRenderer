//
// Created by scc on 2025/11/2.
//

#include "raster.h"

void Raster::rasterizeLine(const Point& start, const Point& end, std::vector<Point>& results)
{
    Point p0 = start, p1 = end;
    if(p0.x > p1.x && p0.y > p1.y)
    {
        std::swap(p0, p1);
    }

    bool flip = false;

    if(p0.y > p1.y)
    {
        p0.y = -p0.y;
        p1.y = -p1.y;
        flip = true;
    }

    int deltaY = p1.y - p0.y, deltaX = p1.x - p0.x;
    bool swap = false;

    if(deltaX < deltaY)
    {
        std::swap(p0.x, p0.y);
        std::swap(p1.x, p1.y);
        std::swap(deltaX, deltaY);
        swap = true;
    }

    Point resPoint = p0, startPoint = p0;
    int p = 2 * deltaY + deltaX;
    while(startPoint.x <= p1.x)
    {
        resPoint.x = startPoint.x;
        resPoint.y = startPoint.y;

        if(swap)
        {
            std::swap(resPoint.x, resPoint.y);
        }

        if(flip)
        {
            resPoint.x = -resPoint.x;
            resPoint.y = -resPoint.y;
        }

        results.emplace_back(resPoint);
        ++startPoint.x;

        if(p >= 0)
        {
            startPoint.y += 1;
            p -= 2 * deltaX;
        }

        p += 2 * deltaY;
    }
}

void Raster::rasterTriangle(const Point& p0, const Point& p1, const Point& p2, std::vector<Point>& results)
{
    int min_x = std::min(p0.x, std::min(p1.x, p2.x));
    int max_x = std::max(p0.x, std::max(p1.x, p2.x));
    int min_y = std::min(p0.y, std::min(p1.y, p2.y));
    int max_y = std::max(p0.y, std::max(p1.y, p2.y));

    for(int x = min_x; x <= max_x; ++x)
    {
        for(int y = min_y; y <= max_y; ++y)
        {
            int pp0_x = p0.x - x, pp0_y = p0.y - y;
            int pp1_x = p1.x - x, pp1_y = p1.y - y;
            int pp2_x = p2.x - x, pp2_y = p2.y - y;

            int cross_p0p1 = pp0_x * pp1_y - pp0_y * pp1_x;
            int cross_p1p2 = pp1_x * pp2_y - pp1_y * pp2_x;
            int cross_p2p0 = pp2_x * pp0_y - pp2_y * pp0_x;

            bool res = (cross_p0p1 > 0 && cross_p1p2 > 0 && cross_p2p0 > 0) ||
                       (cross_p0p1 < 0 && cross_p1p2 < 0 && cross_p2p0 < 0);

            if(res)
            {
                Point result;
                result.x = x, result.y = y;
                results.push_back(result);
            }
        }
    }
}

void Raster::interpolantLine(const Point& start, const Point& end, Point& target)
{
    int y = end.y - start.y, x = target.y - start.y;
    if(y == 0)
    {
        y = end.x - start.x;
        x = target.x - start.x;
    }

    float weight = (float)x / y;

    target.color.R = static_cast<byte>(start.color.R * (1 - weight)) + end.color.R * weight;
    target.color.G = static_cast<byte>(start.color.G * (1 - weight)) + end.color.G * weight;
    target.color.B = static_cast<byte>(start.color.B * (1 - weight)) + end.color.B * weight;
    target.color.A = static_cast<byte>(start.color.A * (1 - weight)) + end.color.A * weight;
}

void Raster::interpolantTriangle(const Point& p0, const Point& p1, const Point& p2, Point& target)
{
    int p0p1_x = p1.x - p0.x, p0p1_y = p1.y - p0.y;
    int p0p2_x = p2.x - p0.x, p0p2_y = p2.y - p0.y;
    int area = p0p1_x * p0p2_y - p0p1_y * p0p2_x;

    int targetp1_x = p1.x - target.x, targetp1_y = p1.y - target.y;
    int targetp2_x = p2.x - target.x, targetp2_y = p2.y - target.y;
    int target_p1_p2 = std::abs(targetp1_x * targetp2_y - targetp1_y * targetp2_x);
    float p0_weight = (float)target_p1_p2 / area;

    int targetp0_x = p0.x - target.x, targetp0_y = p0.y - target.y;
    int target_p0_p2 = std::abs(targetp0_x * targetp2_y - targetp0_y * targetp2_x);
    float p1_weight = (float)target_p0_p2 / area;

    int target_p0_p1 = std::abs(targetp0_x * targetp1_y - targetp0_y * targetp1_x);
    float p2_weight = (float)target_p0_p1 / area;

    target.color.R = p0.color.R * p0_weight + p1.color.R * p1_weight + p2.color.R * p2_weight;
    target.color.G = p0.color.G * p0_weight + p1.color.G * p1_weight + p2.color.G * p2_weight;
    target.color.B = p0.color.B * p0_weight + p1.color.B * p1_weight + p2.color.B * p2_weight;
    target.color.A = p0.color.A * p0_weight + p1.color.A * p1_weight + p2.color.A * p2_weight;
}