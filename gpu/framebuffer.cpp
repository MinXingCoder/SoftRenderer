#include "framebuffer.h"

FrameBuffer::FrameBuffer(uint32_t width, uint32_t height, void* buffer)
    : mWidth(width)
    , mHeight(height)
{
  if(buffer == nullptr)
  {
    mColorBuffer = new RGBA[width * height];
    mExternBuffer = false;
  }
  else {
    mColorBuffer = (RGBA*)buffer;
    mExternBuffer = true;
  }
}

FrameBuffer::~FrameBuffer()
{
  if(mColorBuffer && !mExternBuffer)
    delete[] mColorBuffer;
}