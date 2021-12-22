#include "StaticMeshIndexed3D.h"

StaticMeshIndexed3D::StaticMeshIndexed3D(bool withPositions, bool withTextureCoordinates, bool withNormals)
    : StaticMesh3D(withPositions, withTextureCoordinates, withNormals) {}

StaticMeshIndexed3D::~StaticMeshIndexed3D()
{
    if (m_isInit) {
        // It's enough to delete indices VBO here, rest of stuff is destructed in super destructor
        m_indicesVBO.deleteVBO();
    }
}

void StaticMeshIndexed3D::deleteMesh()
{
    if (m_isInit) {
        m_indicesVBO.deleteVBO();
        StaticMesh3D::deleteMesh();
    }
}