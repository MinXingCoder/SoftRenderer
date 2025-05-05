#include "shader.h"

#include <valarray>

Shader::Shader() {}

Shader::~Shader() {}

glm::vec4 Shader::getVector(const std::map<uint32_t, BindingDescription>& bindingMap, const std::map<uint32_t, BufferObject*>& bufferMap, const uint32_t& attributeLocation, const uint32_t& index)
{
    auto bindingMapIter = bindingMap.find(attributeLocation);
    if(bindingMapIter == bindingMap.end())
        assert(false);

    auto bufferMapIter = bufferMap.find(bindingMapIter->second.mVobId);

    size_t dataOffset = bindingMapIter->second.mStride * index + bindingMapIter->second.mOffset;

    const byte* buffer = bufferMapIter->second->getBuffer() + dataOffset;

    glm::vec4 result;

    for(int i = 0; i < bindingMapIter->second.mItemSize; ++i)
    {
        result[i] = ((float*)buffer)[i];
    }

    return result;
}

RGBA Shader::vectorToRGBA(const glm::tvec4<float>& v)
{
    RGBA result;
    result.mR = v.x * 255.0;
    result.mG = v.y * 255.0;
    result.mB = v.z * 255.0;
    result.mA = v.w * 255.0;

    return result;
}
