#include "shader.h"

Shader::Shader() {}

Shader::~Shader() {}

math::vec4f Shader::getVector(const std::map<uint32_t, BindingDescription>& bindingMap, 
												 const std::map<uint32_t, BufferObject*>& bufferMap, 
												 const uint32_t& attributeLocation, const uint32_t& index)
{
	auto bindingMapIter = bindingMap.find(attributeLocation);
	if (bindingMapIter == bindingMap.end())
		assert(false);

	auto bufferMapIter = bufferMap.find(bindingMapIter->second.mVboId);

	size_t dataOffset = bindingMapIter->second.mStride * index + bindingMapIter->second.mOffset;
	size_t dataSize = bindingMapIter->second.mItemSize * sizeof(float);

	const byte* buffer = bufferMapIter->second->getBuffer() + dataOffset;

	math::vec4f result;

	memcpy(&result, buffer, dataSize);

	return result;
}

RGBA Shader::vectorToRGBA(const math::vec4f& v)
{
	RGBA result;
	result.mR = v.x * 255.0;
	result.mG = v.y * 255.0;
	result.mB = v.z * 255.0;
	result.mA = v.w * 255.0;

	return result;
}