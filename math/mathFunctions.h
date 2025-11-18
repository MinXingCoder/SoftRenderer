//
// Created by scc on 2025/11/13.
//
#pragma once
#include <glm/glm.hpp>

namespace math
{
    glm::mat4x4 screenMatrix(const uint32_t& width, const uint32_t& height)
    {
        glm::mat4x4 result(1.0f);

        result[0][0] = (float)width / 2.f;
        result[1][1] = (float)height / 2.f;
        result[2][2] = 0.5f;
        result[3][0] = (float)width / 2.f;
        result[3][1] = (float)height / 2.f;
        result[3][2] = 0.5f;
        result[3][3] = 1.f;

        return result;
    }
}