#include "StaticMesh3D.h"

class StaticMeshIndexed3D : public StaticMesh3D
{
public:
    StaticMeshIndexed3D(bool withPositions, bool withTextureCoordinates, bool withNormals);
    virtual ~StaticMeshIndexed3D();

    void deleteMesh() override;

protected:
    Buffer m_indicesVBO;

    int m_numVertices = 0;
    int m_numIndices = 0;
    int m_primitiveRestartIndex = 0;
};