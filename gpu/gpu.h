//
// Created by scc on 2025/11/2.
//
#pragma once
#define sgi Gpu::getInstance()

#include "../global/base.h"

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

private:
    Gpu() = default;
    ~Gpu() = default;

    int m_width {0};
    int m_height {0};

    FrameBuffer* m_buffer {nullptr};
};