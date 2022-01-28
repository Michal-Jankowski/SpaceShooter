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
    static const int POSITION_ATTRIBUTE_INDEX;
    static const int TEXTURE_COORDINATE_ATTRIBUTE_INDEX; 
    static const int NORMAL_ATTRIBUTE_INDEX; 
    static const int TANGENT_ATTRIBUTE_INDEX;
    static const int BITANGENT_ATTRIBUTE_INDEX;

    bool loadModelFromFile(const std::string& path);
    void render(const glm::mat4 model) const;
    void clearData();
    [[nodiscard]] bool hasTransparentMaterials();
private:
    void setVertexAttributesPointers(int numVertices);
    void ReadMeshNormals(const aiScene* scene);
    void ReadMeshUVs(const aiScene* scene);
    int ReadMeshPositions(const aiScene* scene);
    void ReadMeshMaterials(const aiScene* scene);

    bool isInitialized = false;
    std::vector<int> m_meshStartIndices; 
    std::vector<int> m_meshVerticesCount; 
    std::vector<int> m_meshMaterialIndices;
    std::map<int, std::unique_ptr<Material>> materials;
    GLuint m_vao_ind = 0;
    Buffer m_vbo;
};


#endif //SPACESHOOTER_MODELMESH_H
