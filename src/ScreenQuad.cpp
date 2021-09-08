#include "ScreenQuad.hpp"

#include "glad/glad.h"

ScreenQuad::ScreenQuad() {
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    float QuadVertices[]{
        -1.0f, -1.0f, // Bottom Left
        +1.0f, -1.0f, // Bottom Right
        +1.0f, +1.0f, // Top Right

        -1.0f, -1.0f, // Bottom Left
        +1.0f, +1.0f, // Top Right
        -1.0f, +1.0f, // Top Left 
    };

    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(QuadVertices[0]), QuadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(QuadVertices[0]), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

ScreenQuad::~ScreenQuad() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}

void ScreenQuad::Render() {
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(m_VAO);
}
