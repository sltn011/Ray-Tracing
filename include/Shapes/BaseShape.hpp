#ifndef RT_SHAPE_BASESHAPE
#define RT_SHAPE_BASESHAPE

#include <cstdint>

class Shader;

class BaseShape {

public:

    BaseShape();

    BaseShape(BaseShape const &rhs);

    BaseShape(BaseShape &&rhs) noexcept;

    BaseShape &operator=(BaseShape const &rhs);

    BaseShape &operator=(BaseShape &&rhs) noexcept;

    int32_t GetID() const;

    virtual void LoadInShader(Shader &ShaderProgramm);

    virtual void LoadInShader(Shader &ShaderProgramm, int32_t Index);

protected:

    int32_t m_ID;

private:

    static int32_t NextFreeID;

};

#endif