#pragma once
#include "../global/base.h"
#include <stdlib.h>

class BufferObject
{
public:
  BufferObject();
  ~BufferObject();

  BufferObject(const BufferObject&) = delete;

  void setBufferData(size_t dataSize, void* data);

  byte* getBuffer() const;

private:
    size_t mBufferSize{0};
    byte* mBuffer{nullptr};
};