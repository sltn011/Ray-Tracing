#ifndef RT_SHAPES_SPHERE
#define RT_SHAPES_SPHERE

#include "glm/glm.hpp"
#include "Shapes/BaseShape.hpp"

class Shader;


class Sphere : public BaseShape {

public:

    Sphere(glm::vec3 Position, float Radius, glm::vec4 Color = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });

    virtual void LoadInShader(Shader &ShaderProgramm) override;

    virtual void LoadInShader(Shader &ShaderProgramm, int32_t Index) override;

    glm::vec3 m_Position;
    float     m_Radius;
    glm::vec4 m_Color;

};

#endif // RT_SHAPES_SPHERE