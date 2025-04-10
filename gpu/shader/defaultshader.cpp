#include "defaulthader.h"

DefaultShader::DefaultShader() 
{ }

DefaultShader::~DefaultShader()
{ }

VsOutput DefaultShader::vertexShader(const std::map<uint32_t, BindingDescription>& bindingMap, const std::map<uint32_t, BufferObject*>& bufferMap, const uint32_t& index)
{
	VsOutput output;

	math::vec4f position = getVector(bindingMap, bufferMap, 0, index);
	position.w = 1.0f;

	output.mPosition = mProjectionMatrix * mViewMatrix * mModelMatrix * position;

	math::vec4f color = getVector(bindingMap, bufferMap, 1, index);

	output.mColor = color;

	math::vec2f uv = getVector(bindingMap, bufferMap, 2, index);

	output.mUV = uv;

	return output;
}

void DefaultShader::fragmentShader(const VsOutput& input, FsOutput& output)
{
	output.mPixelPos = math::vec2i(static_cast<int>(input.mPosition.x), static_cast<int>(input.mPosition.y));
	output.mDepth = input.mPosition.z;
	output.mColor = vectorToRGBA(input.mColor);
}