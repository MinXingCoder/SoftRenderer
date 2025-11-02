//
// Created by scc on 2025/11/2.
//

#include "framebuffer.h"
#include <string.h>

FrameBuffer::FrameBuffer(const int& width, const int& height, void* frame)
    : m_width(width)
    , m_height(height)
{
    const int array_size = width * height;
    m_data = new RGBA[array_size];

    if(frame == nullptr)
    {
        memset(m_data, 0, sizeof(RGBA) * array_size);
    } else {
        memcpy(m_data, frame, sizeof(RGBA) * array_size);
    }
}

FrameBuffer::~FrameBuffer()
{
    if(m_data != nullptr)
    {
        delete[] m_data;
        m_data = nullptr;
    }
}

void* FrameBuffer::getData() const
{
    return m_data;
}