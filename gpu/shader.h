#pragma once
#include "datastructures.h"
#include "bufferobject.h"
#include <map>

#include <glm/glm.hpp>

class Shader
{
public:
    Shader();
    ~Shader();

    virtual VsOutput vertexShader(const std::map<uint32_t, BindingDescription>& bindingMap,
                                  const std::map<uint32_t, BufferObject*>& bufferMap,
                                  const uint32_t& index) = 0;

    virtual void fragmentShader(const VsOutput& input, FsOutput& output) = 0;

public:
    glm::vec4 getVector(const std::map<uint32_t, BindingDescription>& bindingMap,
                        const std::map<uint32_t, BufferObject*>& bufferMap,
                        const uint32_t& attributeLocation, const uint32_t& index);

    RGBA vectorToRGBA(const glm::tvec4<float>& v);
};
