#pragma once
#include <glm/glm.hpp>
#include "../../utils/Buffer.h"

class Cube
{
public:
    Cube();
    ~Cube();
    void render() const;

private:
    void initializeData();
    void setVertexAttributesPointers() const;
    void renderInternal() const;
    void deleteMesh();
    int getVertexByteSize() const;

    bool m_isInitialized = false;
    GLuint m_vao = 0; 
    Buffer m_vbo, m_ebo; 
    unsigned int VBO, VAO, EBO;

};

