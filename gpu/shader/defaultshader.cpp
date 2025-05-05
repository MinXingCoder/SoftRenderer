#include "defaultshader.h"

DefaultShader::DefaultShader() {}

DefaultShader::~DefaultShader() {}

VsOutput DefaultShader::vertexShader(const std::map<uint32_t, BindingDescription>& bindingMap, const std::map<uint32_t, BufferObject*>& bufferMap, const uint32_t& index)
{
    VsOutput output;

    glm::vec4 position = getVector(bindingMap, bufferMap, 0, index);
    position.w = 1.0f;

    output.mPosition = mProjectionMatrix * mViewMatrix * mModelMatrix * position;

    glm::vec4 color = getVector(bindingMap, bufferMap, 1, index);

    output.mColor = color;

    glm::vec2 uv = getVector(bindingMap, bufferMap, 2, index);

    output.mUV = uv;

    return output;
}

void DefaultShader::fragmentShader(const VsOutput& input, FsOutput& output)
{
    output.mPixelPos = glm::u32vec2(input.mPosition.x, input.mPosition.y);
    output.mDepth = input.mPosition.z;
    output.mColor = vectorToRGBA(input.mColor);
}
