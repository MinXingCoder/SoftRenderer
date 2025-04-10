#include "gpu.h"
#include <algorithm>
#include "raster.h"

GPU* GPU::mInstance = nullptr;

GPU* GPU::getInstance()
{
	if (mInstance == nullptr)
	{
		static GPU gpu;
		mInstance = &gpu;
	}

	return mInstance;
}

GPU::GPU()
{}

GPU::~GPU()
{
	if (mFrameBuffer)
	{
		delete mFrameBuffer;
	}

	for (auto iter : mBufferMap)
	{
		delete iter.second;
	}

	mBufferMap.clear();

	for (auto iter : mVaoMap)
	{
		delete iter.second;
	}

	mVaoMap.clear();
}

void GPU::initSurface(const uint32_t& width, const uint32_t& height, void* buffer)
{
	mFrameBuffer = new FrameBuffer(width, height, buffer);
	mScreenMatrix = math::screenMatrix<float>(width - 1, height - 1);
}

void GPU::clear()
{
	size_t pixelSize = mFrameBuffer->mWidth * mFrameBuffer->mHeight;
	std::fill_n(mFrameBuffer->mColorBuffer, pixelSize, RGBA(0, 0, 0, 0));
}

uint32_t GPU::genBuffer()
{
	++mBufferCounter;

	mBufferMap.insert(std::make_pair(mBufferCounter, new BufferObject()));

	return mBufferCounter;
}

void GPU::deleteBuffer(const uint32_t& bufferId)
{
	auto iter = mBufferMap.find(bufferId);
	if (iter != mBufferMap.end())
	{
		delete iter->second;
	}
	else {
		return;
	}

	mBufferMap.erase(iter);
}

void GPU::bindBuffer(const uint32_t& bufferType, const uint32_t& bufferId)
{
	if (bufferType == ARRAY_BUFFER)
	{
		mCurrentVBO = bufferId;
	}
	else if (bufferType == ELEMENT_ARRAY_BUFFER)
	{
		mCurrentEBO = bufferId;
	}
}

void GPU::bufferData(const uint32_t& bufferType, size_t dataSize, void* data)
{
	decltype(mBufferMap.begin()) item;

	if (bufferType == ARRAY_BUFFER)
	{
		item = mBufferMap.find(mCurrentVBO);
	}
	else if (bufferType == ELEMENT_ARRAY_BUFFER)
	{
		item = mBufferMap.find(mCurrentEBO);
	}

	if (item == mBufferMap.end()) assert(false);
	item->second->setBufferData(dataSize, data);
}

uint32_t GPU::getVertexArray()
{
	++mVaoCounter;

	mVaoMap.insert(std::make_pair(mVaoCounter, new VertexArrayObject()));

	return mVaoCounter;
}

void GPU::deleteVertexArray(const uint32_t& vaoId)
{
	auto iter = mVaoMap.find(vaoId);
	if (iter != mVaoMap.end())
	{
		delete iter->second;
	}
	else {
		return;
	}

	mVaoMap.erase(iter);
}

void GPU::bindVertexArray(const uint32_t& vaoId)
{
	mCurrentVAO = vaoId;
}

void GPU::vertexAttributePointer(const uint32_t& binding, const uint32_t& itemSize, const uint32_t& stride, const uint32_t& offset)
{
	auto iter = mVaoMap.find(mCurrentVAO);
	if (iter == mVaoMap.end())
		assert(false);

	iter->second->set(binding, mCurrentVBO, itemSize, stride, offset);
}

void GPU::printVAO(const uint32_t & vaoId)
{
	auto iter = mVaoMap.find(vaoId);
	if (iter != mVaoMap.end())
	{
		iter->second->print();
	}
}

void GPU::useProgram(Shader* shader)
{
	mShader = shader;
}

void GPU::drawElement(const uint32_t& drawMode, const uint32_t& first, const uint32_t& count)
{
	if (mCurrentVAO == 0 || mShader == nullptr || count == 0)
	{
		return;
	}

	auto vaoIter = mVaoMap.find(mCurrentVAO);
	if (vaoIter == mVaoMap.end())
	{
		std::cerr << "Error: current vao is invalid!" << std::endl;
		return;
	}

	const VertexArrayObject* vao = vaoIter->second;
	auto bindingMap = vao->getBindingMap();

	auto eboIter = mBufferMap.find(mCurrentEBO);
	if (eboIter == mBufferMap.end())
	{
		std::cerr << "Error: current ebo is invalid!" << std::endl;
		return;
	}

	const BufferObject* ebo = eboIter->second;

	std::vector<VsOutput> vsOutputs{};
	vertexShaderStage(vsOutputs, vao, ebo, first, count);

	if (vsOutputs.empty()) return;

	for (auto& output : vsOutputs)
	{
		perspectiveDivision(output);
	}

	for (auto& output : vsOutputs)
	{
		screenMapping(output);
	}

	std::vector<VsOutput> rasterOutputs;
	Raster::rasterize(rasterOutputs, drawMode, vsOutputs);

	if (rasterOutputs.empty()) return;

	FsOutput fsOutput;
	uint32_t pixelPos = 0;
	for (uint32_t i = 0; i < rasterOutputs.size(); ++i)
	{
		mShader->fragmentShader(rasterOutputs[i], fsOutput);
		pixelPos = fsOutput.mPixelPos.y * mFrameBuffer->mWidth + fsOutput.mPixelPos.x;
		mFrameBuffer->mColorBuffer[pixelPos] = fsOutput.mColor;
	}
}

void GPU::vertexShaderStage(
	std::vector<VsOutput>& vsOutputs,
	const VertexArrayObject* vao,
	const BufferObject* ebo,
	const uint32_t first,
	const uint32_t count)
{
	auto bindingMap = vao->getBindingMap();
	byte* indicesData = ebo->getBuffer();

	uint32_t index = 0;
	for (uint32_t i = first; i < first + count; ++i)
	{
		size_t indicesOffset = i * sizeof(uint32_t);
		memcpy(&index, indicesData + indicesOffset, sizeof(uint32_t));

		VsOutput output = mShader->vertexShader(bindingMap, mBufferMap, index);
		vsOutputs.push_back(output);
	}
}

void GPU::perspectiveDivision(VsOutput& vsOutput)
{
	float oneOverW = 1.0f / vsOutput.mPosition.w;

	vsOutput.mPosition *= oneOverW;
	vsOutput.mPosition.w = 1.0f;
}

void GPU::screenMapping(VsOutput& vsOuput)
{
	vsOuput.mPosition = mScreenMatrix * vsOuput.mPosition;
}