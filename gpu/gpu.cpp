//
// Created by scc on 2025/11/2.
//

#include "gpu.h"
#include "framebuffer.h"
#include "raster.h"

Gpu* Gpu::getInstance()
{
    static Gpu gpu;
    return &gpu;
}

bool Gpu::initSurface(void* buffer)
{
    if(buffer == nullptr)
        return false;

    m_buffer = (FrameBuffer*)buffer;

    m_width = m_buffer->getWidth();
    m_height = m_buffer->getHeight();

    return true;
}

void Gpu::drawPoint(const Point& point)
{
    if(point.x < 0 || point.x >= m_width)
        return;

    if(point.y < 0 || point.y >= m_height)
        return;

    int y = m_height - 1 - point.y;

    RGBA* colors = (RGBA*)(m_buffer->getData());
    colors[point.x + y * m_width] = point.color;
}

void Gpu::drawLine(const Point& start, const Point& end)
{
    std::vector<Point> results;
    Raster::rasterizeLine(start, end, results);

    for(size_t i = 0; i < results.size(); ++i)
    {
        drawPoint(results[i]);
    }
}