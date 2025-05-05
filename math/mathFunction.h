#include <glm/glm.hpp>

inline glm::mat4x4 ScreenMatrix(const uint32_t& width, const uint32_t& height)
{
    float widthFloat = static_cast<float>(width) / 2;
    float heightFloat = static_cast<float>(height) / 2;

    glm::mat4x4 result(
        widthFloat, 0, 0, 0,
        0, heightFloat, 0, 0,
        0, 0, 0.5f, 0,
        widthFloat, heightFloat, 0.5f, 1
    );

    return result;
}

inline glm::vec4 Lerp(const glm::vec4& a, const glm::vec4& b, float weight)
{
    return (a * (1 - weight) + b * weight);
}

inline glm::vec2 Lerp(const glm::vec2& a, const glm::vec2& b, float weight)
{
    return (a * (1 - weight) + b * weight);
}

inline glm::vec4 Lerp(const glm::vec4& a, const glm::vec4& b, const glm::vec4& c, float alpha, float beta, float gamma)
{
    return (a * alpha + b * beta + c * gamma);
}

inline glm::vec2 Lerp(const glm::vec2& a, const glm::vec2& b, const glm::vec2& c, float alpha, float beta, float gamma)
{
    return (a * alpha + b * beta + c * gamma);
}

inline float Cross(const glm::ivec2& a, const glm::ivec2& b)
{
    return (a.x * b.y - a.y * b.x);
}

inline float Cross(const glm::vec2& a, const glm::vec2& b)
{
    return (a.x * b.y - a.y * b.x);
}