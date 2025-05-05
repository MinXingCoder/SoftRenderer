#include "bufferobject.h"
#include <string.h>

BufferObject::BufferObject() {}

BufferObject::~BufferObject()
{
  if(mBuffer)
  {
	delete[] mBuffer;
    mBuffer = nullptr;
  }
}

void BufferObject::setBufferData(size_t dataSize, void* data)
{
  	if(mBuffer != nullptr && dataSize > mBufferSize)
    {
      delete[] mBuffer;
      mBuffer = nullptr;
    }

    if(mBuffer == nullptr)
    {
      mBuffer = new byte[dataSize];
      mBufferSize = dataSize;
    }

    memcpy(mBuffer, data, dataSize);
}

byte* BufferObject::getBuffer() const
{
  return mBuffer;
}