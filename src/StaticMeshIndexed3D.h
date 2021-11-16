#include "StaticMesh3D.h"

class StaticMeshIndexed3D : public StaticMesh3D
{
public:
    StaticMeshIndexed3D(bool withPositions, bool withTextureCoordinates, bool withNormals);
    virtual ~StaticMeshIndexed3D();

    void deleteMesh() override;

protected:
    Buffer _indicesVBO; // Our VBO wrapper class holding indices data

    int _numVertices = 0; // Holds the total number of generated vertices
    int _numIndices = 0; // Holds the number of generated indices used for rendering
    int _primitiveRestartIndex = 0; // Index of primitive restart
};