//
// Created by scc on 2025/11/2.
//
#pragma once
#include "../global/base.h"

class FrameBuffer {
public:
    FrameBuffer(const int& width, const int& height, void* frame);
    ~FrameBuffer();

    void* getData() const;

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

private:
    int m_width {0};
    int m_height {0};

    RGBA* m_data {nullptr};
};
