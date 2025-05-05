#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

Image::Image(const uint32_t& width, const uint32_t& height, const RGBA* data)
    : mWidth(width)
    , mHeight(height)
{
    if(data)
    {
        mData = new RGBA[width * height];
        memcpy(mData, data, width * height * sizeof(RGBA));
    }
}

Image::~Image()
{
    if(mData)
    {
        delete[] mData;
    }
}

Image* Image::readImage(const std::string& path)
{
    int channel{}, x{}, y{};

    // stbi 库读取图片是左上角为原点, 向下为 y 轴, 需要进行翻转
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &x, &y, &channel, STBI_rgb_alpha);

    int xy = x * y * 4;
    Image* img = new Image(x, y, (RGBA*)data);

    stbi_image_free(data);

    return img;
}

bool Image::writeImage(
        const std::string& path,
        const uint32_t& width,
        const uint32_t& height,
        const uint32_t& channel,
        const RGBA* data)
{
    int result = stbi_write_png(path.c_str(), width, height, channel, data, width * 4);
    if(result) return true;
    return false;
}

void Image::destroy(const Image* image)
{
    if(image)
        delete image;
}
