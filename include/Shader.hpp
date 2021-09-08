#ifndef RT_SHADER
#define RT_SHADER

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Exception.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader {

    unsigned int m_programmID;
    bool         m_showWarnings;

    unsigned int compileGLShader(
        char const *sourceCode,
        int shaderType
    );

    bool shaderCorrectlyCompiled(
        unsigned int shaderId
    );

    [[noreturn]] void reportShaderCompileError(
        unsigned int shaderId
    );

    bool programmCorrectlyLinked(
        unsigned int programmId
    );

    [[noreturn]] void reportProgrammLinkError(
        unsigned int programmId
    );

    void warnInvalidUniformLocation(
        std::string const &name
    );

public:

    Shader(
        std::string vertexSourcePath,
        std::string fragmentSourcePath
    );

    Shader(
        std::string vertexSourcePath,
        std::string geometrySourcePath,
        std::string fragmentSourcePath
    );

    Shader(
        Shader const &rhs
    ) = delete;

    Shader(
        Shader &&rhs
    ) noexcept;

    Shader &operator=(
        Shader const &rhs
        ) = delete;

    Shader &operator=(
        Shader &&rhs
        ) noexcept;

    ~Shader(
    );

    unsigned int id(
    ) const;

    void use(
    );

    void showWarnings(
        bool value
    );

    bool setUniformBool(
        std::string const &name,
        bool val
    );

    bool setUniformInt(
        std::string const &name,
        int val
    );

    bool setUniformFloat(
        std::string const &name,
        float val
    );

    bool setUniformMatrix4(
        std::string const &name,
        glm::mat4 const &val,
        bool doTranspose = false
    );

    bool setUniformVec3(
        std::string const &name,
        glm::vec3 const &val
    );

    bool setUniformVec4(
        std::string const &name,
        glm::vec4 const &val
    );

    bool uniformBlockBinding(
        std::string const &blockName,
        size_t bindingPointIndex
    );
};

#endif // RT_SHADER