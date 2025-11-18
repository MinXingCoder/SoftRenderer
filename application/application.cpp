//
// Created by scc on 2025/11/2.
//
#include "application.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdio.h>
#include <GLFW/glfw3.h>
#include "../gpu/framebuffer.h"

GLuint gImgTexture;

Application* Application::getInstance()
{
    static Application instance;
    return &instance;
}

bool Application::initApplication(const int& width, const int& height, const std::string& title)
{
    m_width = width;
    m_height = height;

    glfwSetErrorCallback([](int error, const char* description)
    {
        fprintf(stderr, "GLFW Error %d: %s\n", error, description);
    });
    if(!glfwInit())
        return false;

#if defined(__APPLE__)
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(m_window == nullptr)
        return false;

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);  // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    if(m_buffer == nullptr)
    {
        m_buffer = new FrameBuffer(width, height, nullptr);
    }

    glDisable(GL_CULL_FACE);

    glGenTextures(1, &gImgTexture);
    glBindTexture(GL_TEXTURE_2D, gImgTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

int Application::windowShouldClose()
{
    if(m_window == nullptr) return 1;
    return glfwWindowShouldClose(m_window);
}

void Application::pollEvents()
{
    glfwPollEvents();
}

void Application::beginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                                    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, m_buffer->getData());

    ImGui::Begin("Learn Graphics", nullptr, window_flags);
}

void Application::render()
{
    ImGui::Image((ImTextureID)(intptr_t)gImgTexture, ImVec2(m_width, m_height));
}

void Application::endFrame()
{
    ImGui::End();
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
                clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(m_window);
}

void Application::destroy()
{
    //Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwDestroyWindow(m_window);
    glfwTerminate();

    if(m_buffer)
    {
        delete m_buffer;
    }
}

void* Application::getFrameBuffer() const
{
    return m_buffer;
}
