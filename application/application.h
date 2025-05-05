#pragma once
#include <stdint.h>

#define winApp Application::getInstance()

class GLFWwindow;
class FrameBuffer;

class Application
{
public:
  static Application* getInstance();

  bool initApplication(const uint32_t& width, const uint32_t& height);

  void close();

  bool peekMessage();

  void beginFrame();

  void endFrame();

  void show();

  uint32_t getWidth() const;

  uint32_t getHeight() const;

  void* getFrameBuffer() const;

private:
  void InitTexture();

  GLFWwindow* mWindow {nullptr};
  FrameBuffer* mFrameBuffer {nullptr};

  uint32_t mWidth{ 0 };
  uint32_t mHeight{ 0 };
};