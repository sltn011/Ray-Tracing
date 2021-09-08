#include "Shapes/BaseShape.hpp"

BaseShape::BaseShape() {
    m_ID = NextFreeID++;
}

int32_t BaseShape::GetID() const {
    return m_ID;
}

int32_t BaseShape::NextFreeID = 0;
