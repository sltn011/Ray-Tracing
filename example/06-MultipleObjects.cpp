#include <iostream>
#include <fstream>

#include "Camera.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Shapes/Sphere.hpp"
#include "WindowManager.hpp"


constexpr float AspectRation = 16.0f / 9.0f;
constexpr int ImageWidth = 1000;
constexpr int ImageHeight = static_cast<int>(ImageWidth / AspectRation);


int main() {
    WindowManager Manager(ImageWidth, ImageHeight, 256);
    Camera Cam(glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 0.0f, 0.0f, -1.0f }, 2.0f);

    Scene RenderScene(Cam);
    auto &Spheres = RenderScene.GetShapes(ShapeTypes::ST_Sphere);
    Spheres.emplace_back(std::make_unique<Sphere>(glm::vec3{ 0.0f, 0.0f, -3.0f }, 1.0f));
    Spheres.emplace_back(std::make_unique<Sphere>(glm::vec3{ 0.0f, 0.0f, -15.0f }, 10.0f));
    Spheres.emplace_back(std::make_unique<Sphere>(glm::vec3{ -0.3f, -0.1f, -1.0f }, 0.25f));
    Spheres.emplace_back(std::make_unique<Sphere>(glm::vec3{ 0.0f, -100.0f, -3.0f }, 99.0f));
    
    Shader ShaderProgramm("shaders/06-MultipleObjects.vert", "shaders/06-MultipleObjects.frag");
    
    RenderScene.LoadInShader(ShaderProgramm);
    
    Manager.Render(ShaderProgramm);
    
    Manager.SaveImagePNG("images/06-1-MultipleObjects.png");
}