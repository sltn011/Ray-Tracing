#include "Shapes/BaseShape.hpp"

BaseShape::BaseShape() {
    m_ID = NextFreeID++;
}

BaseShape::BaseShape(BaseShape const &rhs) {
    m_ID = rhs.m_ID;
}

BaseShape::BaseShape(BaseShape &&rhs) noexcept {
    m_ID = rhs.m_ID;
}

BaseShape &BaseShape::operator=(BaseShape const &rhs) {
    m_ID = rhs.m_ID;
    return *this;
}

BaseShape &BaseShape::operator=(BaseShape &&rhs) noexcept {
    m_ID = rhs.m_ID;
    return *this;
}

int32_t BaseShape::GetID() const {
    return m_ID;
}

void BaseShape::LoadInShader(Shader &ShaderProgramm) {
}

void BaseShape::LoadInShader(Shader &ShaderProgramm, int32_t Index) {
}

int32_t BaseShape::NextFreeID = 0;
