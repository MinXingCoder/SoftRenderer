#include "application.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include "../gpu/framebuffer.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

Application* Application::getInstance()
{
    static Application app;
    return &app;
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

static GLuint gImageTexture;

bool Application::initApplication(const uint32_t& width, const uint32_t& height)
{
    mWidth = width;
    mHeight = height;

    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
        return false;

    mWindow = glfwCreateWindow(mWidth, mHeight, "SoftRender Example", nullptr, nullptr);
    if (!mWindow)
        return false;

    glfwMakeContextCurrent(mWindow);
    glfwSwapInterval(1);    // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    ImGui_ImplOpenGL2_Init();

    if (!mFrameBuffer)
    {
        mFrameBuffer = new FrameBuffer(mWidth, mHeight, nullptr);
        memset(mFrameBuffer->mColorBuffer, 0, sizeof(RGBA) * mWidth * mHeight);
    }

    InitTexture();

    return true;
}

void Application::InitTexture()
{
    glGenTextures(1, &gImageTexture);
    glBindTexture(GL_TEXTURE_2D, gImageTexture);

    // Setup filtering paramters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
}

void Application::close()
{
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(mWindow);
    glfwTerminate();

    if (mFrameBuffer)
        delete mFrameBuffer;
}

bool Application::peekMessage()
{
    bool alive = glfwWindowShouldClose(mWindow);
    glfwPollEvents();
    return alive;
}

void Application::beginFrame()
{
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("SoftRender");
}

void Application::endFrame()
{
    ImGui::End();

    ImGui::Render();
    glViewport(0, 0, mWidth, mHeight);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    glfwMakeContextCurrent(mWindow);
    glfwSwapBuffers(mWindow);
}

void Application::show()
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mFrameBuffer->mColorBuffer);
    ImGui::Image((ImTextureID)(intptr_t)gImageTexture, ImVec2(mWidth, mHeight));
}

uint32_t Application::getWidth() const
{
    return mWidth;
}

uint32_t Application::getHeight() const
{
    return mHeight;
}

void* Application::getFrameBuffer() const
{
    return (void*)mFrameBuffer;
}