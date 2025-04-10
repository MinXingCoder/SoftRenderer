#include "vao.h"

VertexArrayObject::VertexArrayObject() {}

VertexArrayObject::~VertexArrayObject() {}

void VertexArrayObject::set(size_t binding, size_t vboId, size_t itemSize, size_t stride, size_t offset)
{
	auto iter = mBindingMap.find(binding);

	if (iter == mBindingMap.end())
	{
		iter = mBindingMap.insert(std::make_pair(binding, BindingDescription())).first;
	}

	auto& item = iter->second;
	item.mVboId = vboId;
	item.mItemSize = itemSize;
	item.mStride = stride;
	item.mOffset = offset;
}

std::map<uint32_t, BindingDescription> VertexArrayObject::getBindingMap() const
{
	return mBindingMap;
}

void VertexArrayObject::print()
{
	std::cout << "VAO Attribute Map is:" << std::endl;
	for (auto& item : mBindingMap)
	{
		std::cout << "Binding ID:" << item.first << std::endl;
		std::cout << "----VBO ID:" << item.second.mVboId << std::endl;
		std::cout << "----ItemSize:" << item.second.mItemSize << std::endl;
		std::cout << "----Stride:" << item.second.mStride << std::endl;
		std::cout << "----Offset" << item.second.mOffset << std::endl;
	}
}