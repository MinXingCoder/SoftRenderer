//
// Created by scc on 2025/11/8.
//
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Image.h"

Image* Image::createImage(const std::string& path)
{
    int width{0}, height{0}, channel{0};

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channel, 0);

    Image* img = new Image(width, height, data);

    stbi_image_free(data);

    return img;
}

void Image::destroyImage(const Image* image)
{
    if(image)
    {
        delete image;
        image = nullptr;
    }
}

Image::Image(const int& width, const int& height, unsigned char* data)
{
    const int array_size = width * height;

    m_data = new RGBA[array_size];

    for(int i = 0; i < array_size; ++i)
    {
        m_data[i].R = data[0];
        m_data[i].G = data[1];
        m_data[i].B = data[2];
        m_data[i].A = 255;
        data += 3;
    }
    m_width = width;
    m_height = height;
}

Image::~Image()
{
    if(m_data)
    {
        delete[] m_data;
        m_data = nullptr;
    }
}

RGBA Image::getPointColor(int x, int y) const
{
    if((x < 0 && x >= m_width) || (y < 0 && y >= m_height))
        return RGBA{0, 0, 0, 0};
    int position = y * m_width + x;
    return m_data[position];
}
