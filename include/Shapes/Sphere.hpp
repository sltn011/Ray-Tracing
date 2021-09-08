#ifndef RT_SHAPES_SPHERE
#define RT_SHAPES_SPHERE

#include "glm/glm.hpp"

class Shader;


class Sphere {

public:

    Sphere(glm::vec3 Position, float Radius, glm::vec4 Color);

    void LoadInShader(Shader &ShaderProgramm);

    void LoadInShader(Shader &ShaderProgramm, int32_t Index);

    glm::vec3 m_Position;
    float     m_Radius;
    glm::vec4 m_Color;

};

#endif // RT_SHAPES_SPHERE