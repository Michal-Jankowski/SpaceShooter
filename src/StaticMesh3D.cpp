#include "StaticMesh3D.h"
#include "glm/glm.hpp"
const int StaticMesh3D::POSITION_ATTRIBUTE_INDEX = 0;
const int StaticMesh3D::TEXTURE_COORDINATE_ATTRIBUTE_INDEX = 1;
const int StaticMesh3D::NORMAL_ATTRIBUTE_INDEX = 2;

StaticMesh3D::StaticMesh3D(bool withPositions, bool withTextureCoordinates, bool withNormals)
    : m_hasPositions(withPositions)
    , m_hasTexCoords(withTextureCoordinates)
    , m_hasNormals(withNormals) {}

StaticMesh3D::~StaticMesh3D()
{
    deleteMesh();
}

void StaticMesh3D::deleteMesh()
{
    if (!m_isInit) {
        return;
    }

    glDeleteVertexArrays(1, &m_vao);
    m_vbo.deleteVBO();

    m_isInit = false;
}

bool StaticMesh3D::hasPositions() const
{
    return m_hasPositions;
}

bool StaticMesh3D::hasTextureCoordinates() const
{
    return m_hasTexCoords;
}

bool StaticMesh3D::hasNormals() const
{
    return m_hasNormals;
}

int StaticMesh3D::getVertexByteSize() const
{
    int result = 0;
    if (hasPositions()) {
        result += sizeof(glm::vec3);
    }
    if (hasTextureCoordinates()) {
        result += sizeof(glm::vec2);
    }
    if (hasNormals()) {
        result += sizeof(glm::vec3);
    }

    return result;
}

void StaticMesh3D::setVertexAttributesPointers(int numVertices)
{
    uint64_t offset = 0;
    if (hasPositions())
    {
        glEnableVertexAttribArray(POSITION_ATTRIBUTE_INDEX);
        glVertexAttribPointer(POSITION_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void*>(offset));

        offset += sizeof(glm::vec3) * numVertices;
    }

    if (hasTextureCoordinates())
    {
        glEnableVertexAttribArray(TEXTURE_COORDINATE_ATTRIBUTE_INDEX);
        glVertexAttribPointer(TEXTURE_COORDINATE_ATTRIBUTE_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), reinterpret_cast<void*>(offset));

        offset += sizeof(glm::vec2) * numVertices;
    }

    if (hasNormals())
    {
        glEnableVertexAttribArray(NORMAL_ATTRIBUTE_INDEX);
        glVertexAttribPointer(NORMAL_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void*>(offset));

        offset += sizeof(glm::vec3) * numVertices;
    }
}