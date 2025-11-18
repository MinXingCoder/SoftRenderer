//
// Created by scc on 2025/11/2.
//
#pragma once
#define sgi Gpu::getInstance()

#include "../global/base.h"
#include "../application/Image.h"

class FrameBuffer;

class Gpu
{
public:
    Gpu(const Gpu&) = delete;
    Gpu& operator=(const Gpu&) = delete;

    static Gpu* getInstance();

    bool initSurface(void* buffer);

    void drawPoint(const Point& point);

    void drawLine(const Point& start, const Point& end);

    void drawTriangle(const Point& p0, const Point& p1, const Point& p2);

    void drawImage(const Image* image);

    void clear();

private:
    Gpu() = default;
    ~Gpu() = default;

    int m_width {0};
    int m_height {0};

    FrameBuffer* m_buffer {nullptr};
};