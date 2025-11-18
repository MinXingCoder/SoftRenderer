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
        Raster::interpolantLine(start, end, results[i]);
        drawPoint(results[i]);
    }
}

void Gpu::drawTriangle(const Point& p0, const Point& p1, const Point& p2)
{
    std::vector<Point> results;
    Raster::rasterTriangle(p0, p1, p2, results);

    for(size_t i = 0; i < results.size(); ++i)
    {
        Raster::interpolantTriangle(p0, p1, p2, results[i]);
        drawPoint(results[i]);
    }
}

void Gpu::drawImage(const Image* image)
{
    int width = image->getWidth();
    int height = image->getHeight();

    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            Point point;
            point.x = j, point.y = i, point.color = image->getPointColor(j, i);
            drawPoint(point);
        }
    }
}

void Gpu::clear()
{
    int array_size = m_width * m_height;
    memset(m_buffer->getData(), 0, array_size * sizeof(RGBA));
}
