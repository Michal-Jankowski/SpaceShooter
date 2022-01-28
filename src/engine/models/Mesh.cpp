#include "Mesh.h"
#include <glm/glm.hpp>

const int Mesh::POSITION_ATTRIBUTE_INDEX = 0;
const int Mesh::TEXTURE_COORDINATE_ATTRIBUTE_INDEX = 1;
const int Mesh::NORMAL_ATTRIBUTE_INDEX = 2;

Mesh::Mesh(bool withPositions, bool withTextureCoordinates, bool withNormals)
    : m_hasPositions(withPositions)
    , m_hasTextureCoordinates(withTextureCoordinates)
    , m_hasNormals(withNormals) {}

Mesh::~Mesh()
{
    deleteMesh();
}

void Mesh::deleteMesh()
{
    if (!m_isInitialized) {
        return;
    }

    glDeleteVertexArrays(1, &m_vao);
    m_vbo.deleteBuffer();

    m_isInitialized = false;
}

void Mesh::setVertexAttributesPointers(int numVertices)
{
    uint64_t offset = 0;
    glEnableVertexAttribArray(POSITION_ATTRIBUTE_INDEX);
    glVertexAttribPointer(POSITION_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void*>(offset));
    offset += sizeof(glm::vec3) * numVertices;

    glEnableVertexAttribArray(TEXTURE_COORDINATE_ATTRIBUTE_INDEX);
    glVertexAttribPointer(TEXTURE_COORDINATE_ATTRIBUTE_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), reinterpret_cast<void*>(offset));
    offset += sizeof(glm::vec2) * numVertices;

    glEnableVertexAttribArray(NORMAL_ATTRIBUTE_INDEX);
    glVertexAttribPointer(NORMAL_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void*>(offset));
    offset += sizeof(glm::vec3) * numVertices;
}
