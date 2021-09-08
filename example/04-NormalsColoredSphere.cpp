#include <iostream>
#include <fstream>

#include "Camera.hpp"
#include "Shader.hpp"
#include "Shapes/Sphere.hpp"
#include "WindowManager.hpp"

constexpr float AspectRation = 16.0f / 9.0f;
constexpr int ImageWidth = 800;
constexpr int ImageHeight = static_cast<int>(ImageWidth / AspectRation);


int main() {
    WindowManager Manager(ImageWidth, ImageHeight);
    Camera Cam(glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 0.0f, 0.0f, -1.0f }, 2.0f);
    Sphere Obj(glm::vec3{ 0.0f, 0.0f, -3.0f }, 1.0f, glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
    
    Shader ShaderProgramm("shaders/04-NormalsColoredSphere.vert", "shaders/04-NormalsColoredSphere.frag");
    
    Cam.LoadInShader(ShaderProgramm);
    Obj.LoadInShader(ShaderProgramm);
    
    Manager.Render(ShaderProgramm);
    
    Manager.SaveImagePNG("images/04-1-NormalsColoredSphere.png");
}