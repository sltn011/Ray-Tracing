#ifndef RT_CAMERA
#define RT_CAMERA

#include "glm/glm.hpp"

class Shader;

struct Camera {

    Camera();

    Camera(glm::vec3 Position, glm::vec3 Direction, float ViewportWidth);

    void LoadInShader(Shader &ShaderProgramm);

    glm::vec3 m_Position;
    glm::vec3 m_Direction;
    float     m_ViewportWidth;
};

#endif // RT_CAMERA
