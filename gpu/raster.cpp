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