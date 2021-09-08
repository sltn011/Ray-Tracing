#include "Camera.hpp"

#include "Shader.hpp"

Camera::Camera(glm::vec3 Position, glm::vec3 Direction, float ViewportWidth) {
    m_Position = Position;
    m_Direction = Direction;
    m_ViewportWidth = ViewportWidth;
}

void Camera::LoadInShader(Shader &ShaderProgramm) {
    ShaderProgramm.use();
    ShaderProgramm.setUniformVec3("UCamera.Position", m_Position);
    ShaderProgramm.setUniformVec3("UCamera.Direction", glm::normalize(m_Direction));
    ShaderProgramm.setUniformFloat("UCamera.ViewportWidth", m_ViewportWidth);
}
