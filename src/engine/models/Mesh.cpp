#include "Mesh.h"
#include <glm/glm.hpp>

const int Mesh::POSITION_ATTRIBUTE_INDEX = 0;
const int Mesh::TEXTURE_COORDINATE_ATTRIBUTE_INDEX = 1;
const int Mesh::NORMAL_ATTRIBUTE_INDEX = 2;

Mesh::Mesh(bool withPositions, bool withTextureCoordinates, bool withNormals)
    : _hasPositions(withPositions)
    , _hasTextureCoordinates(withTextureCoordinates)
    , _hasNormals(withNormals) {}

Mesh::~Mesh()
{
    deleteMesh();
}

void Mesh::deleteMesh()
{
    if (!_isInitialized) {
        return;
    }

    glDeleteVertexArrays(1, &_vao);
    _vbo.deleteBuffer();

    _isInitialized = false;
}

bool Mesh::hasPositions() const
{
    return _hasPositions;
}

bool Mesh::hasTextureCoordinates() const
{
    return _hasTextureCoordinates;
}

bool Mesh::hasNormals() const
{
    return _hasNormals;
}

int Mesh::getVertexByteSize() const
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

void Mesh::setVertexAttributesPointers(int numVertices)
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
