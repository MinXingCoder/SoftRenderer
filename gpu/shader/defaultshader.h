#pragma once
#include "../shader.h"

class DefaultShader : public Shader
{
public:
    DefaultShader();
    ~DefaultShader();

    VsOutput vertexShader(const std::map<uint32_t, BindingDescription>& bindingMap, const std::map<uint32_t, BufferObject*>& bufferMap, const uint32_t& index) override;

    void fragmentShader(const VsOutput& input, FsOutput& output) override;

public:
    // uniforms
    glm::mat4 mModelMatrix;
    glm::mat4 mViewMatrix;
    glm::mat4 mProjectionMatrix;
};
