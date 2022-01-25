#include "Cube.h"
#include <glm/glm.hpp>
#include <iostream>

constexpr GLfloat vertices[] = {
   -0.5f, 0.5f, 0.5f,      0, 1,       0, 0, 1,     // 0
    0.5f, 0.5f, 0.5f,      1, 1,       0, 0, 1,     // 1
    0.5f, -0.5f, 0.5f,     1, 0,       0, 0, 1,     // 2
   -0.5f, -0.5f, 0.5f,     0, 0,       0, 0, 1,     // 3
    0.5f, 0.5f, -0.5f,     0, 1,       0, 0, -1,    // 4
   -0.5f, 0.5f, -0.5f,     1, 1,       0, 0, -1,    // 5
   -0.5f, -0.5f, -0.5f,    1, 0,       0, 0, -1,    // 6
    0.5f, -0.5f, -0.5f,    0, 0,       0, 0, -1,    // 7
   -0.5f, 0.5f, -0.5f,     0, 1,      -1, 0, 0,     // 8
   -0.5f, 0.5f, 0.5f,      1, 1,      -1, 0, 0,     // 9
   -0.5f, -0.5f, 0.5f,     1, 0,      -1, 0, 0,     // 10
   -0.5f, -0.5f, -0.5f,    0, 0,      -1, 0, 0,     // 11
    0.5f, 0.5f, 0.5f,      0, 1,       1, 0, 0,     // 12
    0.5f, 0.5f, -0.5f,     1, 1,       1, 0, 0,     // 13
    0.5f, -0.5f, -0.5f,    1, 0,       1, 0, 0,     // 14
    0.5f, -0.5f,  0.5f,    0, 0,       1, 0, 0,     // 15
   -0.5f, 0.5f, -0.5f,     0, 1,       0, 1, 0,     // 16
    0.5f,  0.5f, -0.5f,    1, 1,       0, 1, 0,     // 17
    0.5f, 0.5f, 0.5f,      1, 0,       0, 1, 0,     // 18
   -0.5f, 0.5f, 0.5f,      0, 0,       0, 1, 0,     // 19
   -0.5f, -0.5f, 0.5f,     0, 1,       0, -1, 0,    // 20
    0.5f, -0.5f, 0.5f,     1, 1,       0, -1, 0,    // 21
    0.5f, -0.5f, -0.5f,    1, 0,       0, -1, 0,    // 22
   -0.5f, -0.5f, -0.5f,    0, 0,       0, -1, 0     // 23
};

constexpr GLushort verticesIndices[] = {
    0, 1, 2, 
    2, 3, 0,
    4, 5, 6,
    6, 7, 4,
    8, 9, 10,
    10, 11, 8,
    12, 13, 14,
    14, 15, 12,
    16, 17, 18,
    18, 19, 16,
    20, 21, 22,
    22, 23, 20
};

Cube::Cube() {
    initData();
}

Cube::~Cube() {
    deleteCube();
}

void Cube::render() const {
    if (!m_isInitialized) {
        return;
    }
    glBindVertexArray(m_VAO);
    renderInternal();
}

void Cube::renderInternal() const {
    int bufferSize;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
    const auto drawSize = bufferSize / sizeof(GLushort);
    glDrawElements(GL_TRIANGLES, drawSize, GL_UNSIGNED_SHORT, 0);
}

void Cube::initData() {
    if (m_isInitialized) {
        return;
    }

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(verticesIndices), verticesIndices, GL_STATIC_DRAW);
    setVertexAttributesPointers();
    m_isInitialized = true;
}

void Cube::deleteCube() {
    if (!m_isInitialized) {
        std::cout << "Trying to delete unitialized mesh!";
        return;
    }
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    m_isInitialized = false;
}

void Cube::setVertexAttributesPointers() const {
    constexpr auto positionIndex = 0;
    constexpr auto textureIndex = 1;
    constexpr auto normalIndex = 2;
    constexpr auto vboStride = 8 * sizeof(GLfloat);
    // position attribute
    glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, vboStride, reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(positionIndex);
    // tex coords attribute
    glVertexAttribPointer(textureIndex, 3, GL_FLOAT, GL_FALSE, vboStride, reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(textureIndex);
    // normal attribute
    glVertexAttribPointer(normalIndex, 2, GL_FLOAT, GL_FALSE, vboStride, reinterpret_cast<void*>(5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(normalIndex);
}