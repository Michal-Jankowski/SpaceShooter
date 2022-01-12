//
// Created by aklin on 31.10.2021.
//

#ifndef SPACESHOOTER_MODELMESH_H
#define SPACESHOOTER_MODELMESH_H


#include <string>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <assimp/types.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include "../utils/Buffer.h"
#include "Material.h"

class ModelMesh {
public:
    ~ModelMesh();
    static const int POSITION_ATTRIBUTE_INDEX; // Vertex attribute index of vertex position (0)
    static const int TEXTURE_COORDINATE_ATTRIBUTE_INDEX; // Vertex attribute index of texture coordinate (1)
    static const int NORMAL_ATTRIBUTE_INDEX; // Vertex attribute index of vertex normal (2)
    static const int TANGENT_ATTRIBUTE_INDEX; // Vertex attribute index of vertex normal (2)
    static const int BITANGENT_ATTRIBUTE_INDEX; // Vertex attribute index of vertex normal (2)

    bool loadModelFromFile(const std::string& path);

    void render(const glm::mat4 model) const;

    void clearData();

private:
    std::vector<int> _meshStartIndices; // Indices of where the meshes start in the VBO
    std::vector<int> _meshVerticesCount; // How many vertices are there for every mesh
    std::vector<int> _meshMaterialIndices; // Index of material for every mesh
    std::map<int, std::unique_ptr<Material>> materials;

    GLuint vao_ind = 0;
    Buffer vbo;

    bool isInitialized = false;

    void setVertexAttributesPointers(int numVertices);

    void ReadMeshNormals(const aiScene *scene);
    void ReadMeshUVs(const aiScene *scene);
    int ReadMeshPositions(const aiScene *scene);

    void ReadMeshMaterials(const aiScene *scene);
};


#endif //SPACESHOOTER_MODELMESH_H
