#include "Camera.hpp"

#include "Shader.hpp"

Camera::Camera() {
    m_Position = glm::vec3{ 0.0f, 0.0f, 0.0f };
    m_Direction = glm::vec3{ 0.0f, 0.0f, -1.0f };
    m_ViewportWidth = 2.0f;
}

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
