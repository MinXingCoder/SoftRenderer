#pragma once
#include "dataStructures.h"
#include "framebuffer.h"
#include <map>
#include "bufferobject.h"
#include "vao.h"
#include "../application/image.h"
#include "shader.h"
#include <vector>

#define sgl GPU::getInstance()

class GPU
{
public:
	static GPU* getInstance();
	
	GPU();
	~GPU();

	void initSurface(const uint32_t& width, const uint32_t& height, void* buffer);
	void clear();

	uint32_t genBuffer();

	void deleteBuffer(const uint32_t& bufferId);

	void bindBuffer(const uint32_t& bufferType, const uint32_t& bufferId);

	void bufferData(const uint32_t& bufferType, size_t dataSize, void* data);

	uint32_t getVertexArray();

	void deleteVertexArray(const uint32_t& vaoId);

	void bindVertexArray(const uint32_t& vaoId);

	void vertexAttributePointer(
		const uint32_t& binding,
		const uint32_t& itemSize,
		const uint32_t& stride,
		const uint32_t& offset
	);

	void useProgram(Shader* shader);

	void drawElement(const uint32_t& drawMode, const uint32_t& fisrt, const uint32_t& count);

	void printVAO(const uint32_t& vaoId);

private:
	void vertexShaderStage(
		std::vector<VsOutput>& vsOutputs,
		const VertexArrayObject* vao,
		const BufferObject* ebo,
		const uint32_t first,
		const uint32_t count
	);

	void perspectiveDivision(VsOutput& vsOutput);
	void screenMapping(VsOutput& vsOutput);

private:

	static GPU* mInstance;
	FrameBuffer* mFrameBuffer{ nullptr };

	uint32_t mCurrentVBO{ 0 };
	uint32_t mCurrentEBO{ 0 };
	uint32_t mBufferCounter{ 0 };
	std::map<uint32_t, BufferObject*> mBufferMap;

	uint32_t mCurrentVAO{ 0 };
	uint32_t mVaoCounter{ 0 };
	std::map<uint32_t, VertexArrayObject*> mVaoMap;

	Shader* mShader{ nullptr };
	math::mat4f mScreenMatrix;
};