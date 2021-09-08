#include <iostream>
#include <fstream>

#include "WindowManager.hpp"
#include "Shader.hpp"

#include "ScreenQuad.hpp"

constexpr float AspectRation = 16.0f / 9.0f;
constexpr int ImageWidth = 1000;
constexpr int ImageHeight = static_cast<int>(ImageWidth / AspectRation);

int main() {
    WindowManager Manager(ImageWidth, ImageHeight);

    Shader ShaderProgramm("shaders/02-TestShader.vert", "shaders/02-TestShader.frag");

    Manager.Render(ShaderProgramm);

    Manager.SaveImagePNG("images/02-1-GPUGeneratedTest.png");
}