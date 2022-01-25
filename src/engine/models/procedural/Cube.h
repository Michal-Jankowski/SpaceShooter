#pragma once
#include <glm/glm.hpp>
#include "GLAD/glad.h"

class Cube
{
public:
    Cube();
    ~Cube();
    void render() const;

private:
    void initData();
    void setVertexAttributesPointers() const;
    void renderInternal() const;
    void deleteCube();
    bool m_isInitialized = false;
    GLuint m_VAO{ 0 };
    GLuint m_VBO{ 0 };
    GLuint m_EBO{ 0 };

};

