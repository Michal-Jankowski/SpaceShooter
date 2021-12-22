#pragma once
// GLM
#include <glm/glm.hpp>
#include "../../utils/Buffer.h"

const int CUBE_FRONT_FACE = 1; // Bitmask to render cube front face
const int CUBE_BACK_FACE = 2; // Bitmask to render cube back face
const int CUBE_LEFT_FACE = 4; // Bitmask to render cube left face
const int CUBE_RIGHT_FACE = 8; // Bitmask to render cube right face
const int CUBE_TOP_FACE = 16; // Bitmask to render cube top face
const int CUBE_BOTTOM_FACE = 32; // Bitmask to render cube bottom face
const int CUBE_ALLFACES = CUBE_FRONT_FACE + CUBE_BACK_FACE + CUBE_LEFT_FACE + CUBE_RIGHT_FACE + CUBE_TOP_FACE + CUBE_BOTTOM_FACE; // Bitmask to render cube bottom face

class Cube
{
public:
    Cube(bool withPositions = true, bool withTextureCoordinates = true, bool withNormals = true);
    ~Cube();
    static const int POSITION_ATTRIBUTE_INDEX; // Vertex attribute index of vertex position (0)
    static const int TEXTURE_COORDINATE_ATTRIBUTE_INDEX; // Vertex attribute index of texture coordinate (1)
    static const int NORMAL_ATTRIBUTE_INDEX; // Vertex attribute index of vertex normal (2)

    void render() const;
    void renderPoints() const;
    void renderFaces(int facesBitmask) const;

    static glm::vec3 vertices[36]; // Array of mesh vertices
    static glm::vec2 textureCoordinates[6]; // Array of mesh texture coordinates
    static glm::vec3 normals[6]; // Array of mesh normals

private:
    void initializeData();
    void deleteMesh();
    void setVertexAttributesPointers(int numVertices);
    int getVertexByteSize() const;
    bool m_hasPositions = false; // Flag telling, if we have vertex positions
    bool m_hasTextureCoordinates = false; // Flag telling, if we have texture coordinates
    bool m_hasNormals = false; // Flag telling, if we have vertex normals

    bool m_isInitialized = false; // Is mesh initialized flag
    GLuint m_vao = 0; // VAO ID from OpenGL
    Buffer m_vbo; // Our VBO wrapper class holding static mesh data

};

