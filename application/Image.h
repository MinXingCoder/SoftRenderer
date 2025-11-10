//
// Created by scc on 2025/11/8.
//
#pragma once
#include <string>
#include "../global/base.h"

class Image
{
public:
    static Image* createImage(const std::string& path);
    static void destroyImage(const Image* image);

    Image(const int& width, const int& height, unsigned char* data);
    ~Image();

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    RGBA getPointColor(int x, int y) const;

private:
    int m_width{0};
    int m_height{0};

    RGBA* m_data{nullptr};
};