#include "WindowManager.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Exception.hpp"
#include "ScreenQuad.hpp"
#include "Shader.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <vector>

WindowManager::WindowManager(int32_t Width, int32_t Height, int32_t Samples) {

    if (!glfwInit()) {
        throw Exception("Error initializing GLFW!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, Samples);

    m_Window = glfwCreateWindow(Width, Height, "", NULL, NULL);
    if (!m_Window) {
        CleanUp();
        throw Exception("Error creating window!");
    }

    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        CleanUp();
        throw Exception("Failed to initialize GLAD");
    }

    glEnable(GL_MULTISAMPLE);
    glViewport(0, 0, Width, Height);

    glfwSetWindowUserPointer(m_Window, this);

    auto ResizeCallbackCaller = [](GLFWwindow *Window, int32_t NewWidth, int32_t NewHeight) {
        WindowManager *Manager = static_cast<WindowManager *>(glfwGetWindowUserPointer(Window));
        if (Manager) {
            Manager->ResizeCallback(NewWidth, NewHeight);
        }
    };

    glfwSetFramebufferSizeCallback(m_Window, ResizeCallbackCaller);
}

WindowManager::~WindowManager() {
    CleanUp();
}

bool WindowManager::IsWindowOpen() {
    return !glfwWindowShouldClose(m_Window);
}

GLFWwindow *WindowManager::GetWindow() const {
    return m_Window;
}

void WindowManager::Render(Shader &ShaderProgramm) {

    int ImageWidth, ImageHeight;
    glfwGetWindowSize(m_Window, &ImageWidth, &ImageHeight);

    if (ImageWidth <= 0 || ImageHeight <= 0) {
        throw Exception("Incorrect image size!");
    }

    ShaderProgramm.use();
    ShaderProgramm.setUniformInt("UImageWidth", ImageWidth);
    ShaderProgramm.setUniformInt("UImageHeight", ImageHeight);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ScreenQuad Quad;
    Quad.Render();

    glfwSwapBuffers(m_Window);
}

void WindowManager::SaveImagePNG(std::string const &FilePath) {
    int ScreenWidth, ScreenHeight;
    glfwGetWindowSize(m_Window, &ScreenWidth, &ScreenHeight);

    GLsizei Channels = 3;
    GLsizei Stride = Channels * ScreenWidth;
    Stride += (Stride % 4) ? (4 - Stride % 4) : 0;

    GLsizei BufferSize = Stride * ScreenHeight;

    std::vector<char> Buffer(BufferSize);

    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadBuffer(GL_FRONT);

    glReadPixels(0, 0, ScreenWidth, ScreenHeight, GL_RGB, GL_UNSIGNED_BYTE, Buffer.data());

    stbi_flip_vertically_on_write(true);
    stbi_write_png(FilePath.c_str(), ScreenWidth, ScreenHeight, Channels, Buffer.data(), Stride);
    stbi_flip_vertically_on_write(false);
}

void WindowManager::CleanUp() {
    glfwTerminate();
}

void WindowManager::ResizeCallback(int32_t NewWidth, int32_t NewHeight) {
    glViewport(0, 0, NewWidth, NewHeight);
}
