#pragma once
#include "../global/base.h"
#include <stdint.h>
#include <glm/glm.hpp>

struct BindingDescription
{
    uint32_t mVobId {0};
    size_t mItemSize {0};
    size_t mStride {0};
    size_t mOffset {0};
};

struct VsOutput
{
    glm::vec4 mPosition{0.0f, 0.0f, 0.0f, 1.0f};
    glm::vec4 mColor;
    glm::vec2 mUV;
};

struct FsOutput
{
    glm::u32vec2 mPixelPos;
    float mDepth;
    RGBA mColor;
};