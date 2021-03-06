#include "Shader.hpp"

Shader::Shader(
    std::string vertexSourcePath,
    std::string fragmentSourcePath
) {
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    std::string vertexShaderCode;
    std::string fragmentShaderCode;

    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertexShaderFile.open(vertexSourcePath);
        fragmentShaderFile.open(fragmentSourcePath);

        std::stringstream ssVertexCode, ssFragmentCode;
        ssVertexCode << vertexShaderFile.rdbuf();
        ssFragmentCode << fragmentShaderFile.rdbuf();

        vertexShaderCode = ssVertexCode.str();
        fragmentShaderCode = ssFragmentCode.str();
    }
    catch (std::ifstream::failure e) {
        throw Exception("Error reading shader code from file!");
    }

    unsigned int vertexShaderID = compileGLShader(vertexShaderCode.c_str(), GL_VERTEX_SHADER);
    if (!shaderCorrectlyCompiled(vertexShaderID)) {
        reportShaderCompileError(vertexShaderID);
    }

    unsigned int fragmentShaderID = compileGLShader(fragmentShaderCode.c_str(), GL_FRAGMENT_SHADER);
    if (!shaderCorrectlyCompiled(fragmentShaderID)) {
        reportShaderCompileError(fragmentShaderID);
    }

    m_programmID = glCreateProgram();
    glAttachShader(m_programmID, vertexShaderID);
    glAttachShader(m_programmID, fragmentShaderID);
    glLinkProgram(m_programmID);
    if (!programmCorrectlyLinked(m_programmID)) {
        reportProgrammLinkError(m_programmID);
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    m_showWarnings = false;
}

Shader::Shader(
    std::string vertexSourcePath,
    std::string geometrySourcePath,
    std::string fragmentSourcePath
) {
    std::ifstream vertexShaderFile;
    std::ifstream geometryShaderFile;
    std::ifstream fragmentShaderFile;
    std::string vertexShaderCode;
    std::string geometryShaderCode;
    std::string fragmentShaderCode;

    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    geometryShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertexShaderFile.open(vertexSourcePath);
        geometryShaderFile.open(geometrySourcePath);
        fragmentShaderFile.open(fragmentSourcePath);

        std::stringstream ssVertexCode, ssGeometryCode, ssFragmentCode;
        ssVertexCode << vertexShaderFile.rdbuf();
        ssGeometryCode << geometryShaderFile.rdbuf();
        ssFragmentCode << fragmentShaderFile.rdbuf();

        vertexShaderCode = ssVertexCode.str();
        geometryShaderCode = ssGeometryCode.str();
        fragmentShaderCode = ssFragmentCode.str();
    }
    catch (std::ifstream::failure e) {
        throw Exception("Error reading shader code from file!");
    }

    unsigned int vertexShaderID = compileGLShader(vertexShaderCode.c_str(), GL_VERTEX_SHADER);
    if (!shaderCorrectlyCompiled(vertexShaderID)) {
        reportShaderCompileError(vertexShaderID);
    }

    unsigned int geometryShaderID = compileGLShader(geometryShaderCode.c_str(), GL_GEOMETRY_SHADER);
    if (!shaderCorrectlyCompiled(geometryShaderID)) {
        reportShaderCompileError(geometryShaderID);
    }

    unsigned int fragmentShaderID = compileGLShader(fragmentShaderCode.c_str(), GL_FRAGMENT_SHADER);
    if (!shaderCorrectlyCompiled(fragmentShaderID)) {
        reportShaderCompileError(fragmentShaderID);
    }

    m_programmID = glCreateProgram();
    glAttachShader(m_programmID, vertexShaderID);
    glAttachShader(m_programmID, geometryShaderID);
    glAttachShader(m_programmID, fragmentShaderID);
    glLinkProgram(m_programmID);
    if (!programmCorrectlyLinked(m_programmID)) {
        reportProgrammLinkError(m_programmID);
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(geometryShaderID);
    glDeleteShader(fragmentShaderID);

    m_showWarnings = false;
}

Shader::Shader(
    Shader &&rhs
) noexcept :
    m_programmID{ std::exchange(rhs.m_programmID, 0) },
    m_showWarnings{ rhs.m_showWarnings } {
}

Shader &Shader::operator=(
    Shader &&rhs
    ) noexcept {
    std::swap(m_programmID, rhs.m_programmID);
    std::swap(m_showWarnings, rhs.m_showWarnings);
    return *this;
}

Shader::~Shader(
) {
    glDeleteProgram(m_programmID);
}

unsigned int Shader::id(
) const {
    return m_programmID;
}

void Shader::use(
) {
    glUseProgram(m_programmID);
}

void Shader::showWarnings(
    bool value
) {
    m_showWarnings = value;
}

bool Shader::setUniformBool(
    std::string const &name,
    bool val
) {
    GLint loc = glGetUniformLocation(m_programmID, name.c_str());
    if (loc == -1) {
        if (m_showWarnings) {
            warnInvalidUniformLocation(name);
        }
        return false;
    }
    glUniform1i(loc, (int)val);
    return true;
}

bool Shader::setUniformInt(
    std::string const &name,
    int val
) {
    GLint loc = glGetUniformLocation(m_programmID, name.c_str());
    if (loc == -1) {
        if (m_showWarnings) {
            warnInvalidUniformLocation(name);
        }
        return false;
    }
    glUniform1i(loc, val);
    return true;
}

bool Shader::setUniformFloat(
    std::string const &name,
    float val
) {
    GLint loc = glGetUniformLocation(m_programmID, name.c_str());
    if (loc == -1) {
        if (m_showWarnings) {
            warnInvalidUniformLocation(name);
        }
        return false;
    }
    glUniform1f(loc, val);
    return true;
}

bool Shader::setUniformMatrix4(
    std::string const &name,
    glm::mat4 const &val,
    bool doTranspose
) {
    GLint loc = glGetUniformLocation(m_programmID, name.c_str());
    if (loc == -1) {
        if (m_showWarnings) {
            warnInvalidUniformLocation(name);
        }
        return false;
    }
    glUniformMatrix4fv(loc, 1, doTranspose, glm::value_ptr(val));
    return true;
}

bool Shader::setUniformVec3(
    std::string const &name,
    glm::vec3 const &val
) {
    GLint loc = glGetUniformLocation(m_programmID, name.c_str());
    if (loc == -1) {
        if (m_showWarnings) {
            warnInvalidUniformLocation(name);
        }
        return false;
    }
    glUniform3fv(loc, 1, &(val.x));
    return true;
}

bool Shader::setUniformVec4(
    std::string const &name,
    glm::vec4 const &val
) {
    GLint loc = glGetUniformLocation(m_programmID, name.c_str());
    if (loc == -1) {
        if (m_showWarnings) {
            warnInvalidUniformLocation(name);
        }
        return false;
    }
    glUniform4fv(loc, 1, &(val.x));
    return true;
}

bool Shader::uniformBlockBinding(
    std::string const &blockName,
    size_t bindingPointIndex
) {
    unsigned int blockIndex = glGetUniformBlockIndex(m_programmID, blockName.c_str());
    if (blockIndex == GL_INVALID_INDEX) {
        if (m_showWarnings) {
            std::cerr << "No uniform block with name \"" << blockName << "\" in programm " << m_programmID << std::endl;
        }
        return false;
    }
    glUniformBlockBinding(m_programmID, blockIndex, static_cast<GLuint>(bindingPointIndex));
    return true;
}

unsigned int Shader::compileGLShader(
    char const *sourceCode,
    int shaderType
) {
    unsigned int shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &sourceCode, nullptr);
    glCompileShader(shaderId);
    return shaderId;
}

bool Shader::shaderCorrectlyCompiled(
    unsigned int shaderId
) {
    int correctness;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &correctness);
    return correctness == GL_TRUE;
}

void Shader::reportShaderCompileError(
    unsigned int shaderId
) {
    std::string infoLog(512, ' ');
    glGetShaderInfoLog(shaderId, static_cast<GLsizei>(infoLog.size()), nullptr, infoLog.data());
    throw Exception(infoLog);
}

bool Shader::programmCorrectlyLinked(
    unsigned int programmId
) {
    int correctness;
    glGetProgramiv(programmId, GL_LINK_STATUS, &correctness);
    return correctness == GL_TRUE;
}

void Shader::reportProgrammLinkError(
    unsigned int programmId
) {
    std::string infoLog(512, ' ');
    glGetProgramInfoLog(programmId, static_cast<GLsizei>(infoLog.size()), nullptr, infoLog.data());
    throw Exception(infoLog);
}

void Shader::warnInvalidUniformLocation(
    std::string const &name
) {
    std::cerr << "No uniform object with name \"" << name << "\" in shader " << m_programmID << std::endl;
}