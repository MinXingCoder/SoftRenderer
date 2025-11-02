//
// Created by scc on 2025/11/2.
//
#pragma once
#define winApp Application::getInstance()
#include <string>

class GLFWwindow;
class FrameBuffer;

class Application
{
public:
    Application(const Application&) = delete;
    Application operator=(const Application&) = delete;

    static Application* getInstance();

    bool initApplication(const int& width, const int& height, const std::string& title);

    int windowShouldClose();
    void pollEvents();

    void beginFrame();
    void render();
    void endFrame();

    void destroy();

    void* getFrameBuffer() const;

private:
    Application() = default;
    ~Application() = default;

    int m_width {0};
    int m_height {0};

    GLFWwindow* m_window {nullptr};
    FrameBuffer* m_buffer {nullptr};
};