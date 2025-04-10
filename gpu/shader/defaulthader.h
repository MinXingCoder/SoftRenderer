#pragma once
#include "../shader.h"

class DefaultShader : public Shader
{
public:
	DefaultShader();
	~DefaultShader();

	VsOutput vertexShader(const std::map<uint32_t, BindingDescription>& bindingMap, const std::map<uint32_t, BufferObject*>& bufferMap, const uint32_t& index);

	void fragmentShader(const VsOutput& input, FsOutput& output);

public:
	// uniforms
	math::mat4f mModelMatrix;
	math::mat4f mViewMatrix;
	math::mat4f mProjectionMatrix;
};