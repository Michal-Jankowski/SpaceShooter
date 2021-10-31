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
#include "Buffer.h"

class ModelMesh {
public:
    static const int POSITION_ATTRIBUTE_INDEX; // Vertex attribute index of vertex position (0)
    static const int TEXTURE_COORDINATE_ATTRIBUTE_INDEX; // Vertex attribute index of texture coordinate (1)
    static const int NORMAL_ATTRIBUTE_INDEX; // Vertex attribute index of vertex normal (2)

    bool loadModelFromFile(const std::string& path, const std::string& defaultTextureName = "", const glm::mat4& modelTransformMatrix = glm::mat4(1.0f));

    void render() const;

    void clearData();

private:
    std::string _modelRootDirectoryPath; // Path of the directory where model (and possibly its assets) is located
    std::vector<int> _meshStartIndices; // Indices of where the meshes start in the VBO
    std::vector<int> _meshVerticesCount; // How many vertices are there for every mesh
    std::vector<int> _meshMaterialIndices; // Index of material for every mesh
    std::map<int, std::string> _materialTextureKeys; // Map for index of material -> texture key to be retrieved from TextureManager

    GLuint vao_ind = 0;
    Buffer vbo;

    bool isInitialized;
    static std::string aiStringToStdString(const aiString& aiStringStruct);
    void setVertexAttributesPointers(int numVertices);
};


#endif //SPACESHOOTER_MODELMESH_H
