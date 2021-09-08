#include "Shapes/Sphere.hpp"

#include "Shader.hpp"

#include <string>

Sphere::Sphere(glm::vec3 Position, float Radius, glm::vec4 Color) {
    m_Position = Position;
    m_Radius = Radius;
    m_Color = Color;
}

void Sphere::LoadInShader(Shader &ShaderProgramm) {
    ShaderProgramm.use();
    ShaderProgramm.setUniformInt("USphere.ID", GetID());
    ShaderProgramm.setUniformVec3("USphere.Position", m_Position);
    ShaderProgramm.setUniformFloat("USphere.Radius", m_Radius);
    ShaderProgramm.setUniformVec4("USphere.Color", m_Color);
}

void Sphere::LoadInShader(Shader &ShaderProgramm, int32_t Index) {
    ShaderProgramm.use();
    ShaderProgramm.setUniformInt("USphere[" + std::to_string(Index) + "].ID", GetID());
    ShaderProgramm.setUniformVec3("USphere[" + std::to_string(Index) + "].Position", m_Position);
    ShaderProgramm.setUniformFloat("USphere[" + std::to_string(Index) + "].Radius", m_Radius);
    ShaderProgramm.setUniformVec4("USphere[" + std::to_string(Index) + "].Color", m_Color);
}
