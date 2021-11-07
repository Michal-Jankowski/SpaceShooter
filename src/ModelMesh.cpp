#include "ModelMesh.h"
#include "TextureManager.h"
#include "PathHelper.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <GLAD/glad.h>

const int ModelMesh::POSITION_ATTRIBUTE_INDEX           = 0;
const int ModelMesh::TEXTURE_COORDINATE_ATTRIBUTE_INDEX = 1;
const int ModelMesh::NORMAL_ATTRIBUTE_INDEX             = 2;


bool ModelMesh::loadModelFromFile(const std::string &path) {
    if (isInitialized) {
        clearData();
    }


    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path,
                                             aiProcess_CalcTangentSpace |
                                             aiProcess_GenNormals |
                                             aiProcess_Triangulate |
                                             aiProcess_JoinIdenticalVertices |
                                             aiProcess_SortByPType
                                             | aiProcess_RemoveComponent
                                             | aiProcess_ValidateDataStructure);

    if (!scene) {
        std::cerr << importer.GetErrorString() << std::endl;
        return false;
    }

    glGenVertexArrays(1, &vao_ind);
    glBindVertexArray(vao_ind);

    vbo.createVBO();
    vbo.bindVBO(GL_ARRAY_BUFFER);

    //vert pos, vert normal, uv coord
    const int vertSize = sizeof(aiVector3D) * 2 + sizeof(aiVector2D);

    int vertexCount = ReadMeshPositions(scene);
    ReadMeshUVs(scene);
    ReadMeshNormals(scene);
    ReadMeshMaterials(scene);

    vbo.uploadDataToGPU(GL_STATIC_DRAW);
    setVertexAttributesPointers(vertexCount);
    isInitialized = true;

    return isInitialized;
}

void ModelMesh::ReadMeshMaterials(const aiScene *scene) {
    for(size_t i = 0; i < scene->mNumMaterials; i++)
    {
        const auto materialPtr = scene->mMaterials[i];
        aiString aiTexturePath;
        // TODO: this here is a hack for 64-bit system - Assimp has a problem extracting texture path apparently
        // On 64-bit version, some models report texture count 1 and then it crashes when getting them
        if (materialPtr->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            if (materialPtr->GetTexture(aiTextureType_DIFFUSE, 0, &aiTexturePath) == AI_SUCCESS)
            {
                const std::string textureFileName = aiStringToStdString(aiTexturePath);
                loadMaterialTexture(static_cast<int>(i), textureFileName);
            }
        }
    }
}

int ModelMesh::ReadMeshPositions(const aiScene *scene) {
    auto vertexCount = 0;
    for (size_t i = 0; i < scene->mNumMeshes; i++)
    {
        const auto meshPtr = scene->mMeshes[i];
        auto vertexCountMesh = 0;
        _meshStartIndices.push_back(vertexCount);
        _meshMaterialIndices.push_back(meshPtr->mMaterialIndex);

        for (size_t j = 0; j < meshPtr->mNumFaces; j++)
        {
            const auto& face = meshPtr->mFaces[j];
            if (face.mNumIndices != 3) {
                continue; // Skip non-triangle faces for now
            }

            for (size_t k = 0; k < face.mNumIndices; k++)
            {
                const auto& position = meshPtr->mVertices[face.mIndices[k]];
                vbo.addData(glm::vec3(position.x, position.y, position.z));
            }

            vertexCountMesh += face.mNumIndices;
        }

        vertexCount += vertexCountMesh;
        _meshVerticesCount.push_back(vertexCountMesh);
    }
    return vertexCount;
}

void ModelMesh::ReadMeshUVs(const aiScene *scene) {
    for (size_t i = 0; i < scene->mNumMeshes; i++)
    {
        const auto meshPtr = scene->mMeshes[i];
        for (size_t j = 0; j < meshPtr->mNumFaces; j++)
        {
            const auto& face = meshPtr->mFaces[j];
            if (face.mNumIndices != 3) {
                continue; // Skip non-triangle faces for now
            }

            for (size_t k = 0; k < face.mNumIndices; k++)
            {
                const auto& textureCoord = meshPtr->mTextureCoords[0][face.mIndices[k]];
                vbo.addRawData(&textureCoord, sizeof(aiVector2D));
            }
        }
    }
}

void ModelMesh::ReadMeshNormals(const aiScene *scene) {
    for (size_t i = 0; i < scene->mNumMeshes; i++)
    {
        const auto meshPtr = scene->mMeshes[i];
        for (size_t j = 0; j < meshPtr->mNumFaces; j++)
        {
            const auto& face = meshPtr->mFaces[j];
            if (face.mNumIndices != 3) {
                continue; // Skip non-triangle faces for now
            }

            for (size_t k = 0; k < face.mNumIndices; k++)
            {
                const auto& normal = meshPtr->HasNormals() ? meshPtr->mNormals[face.mIndices[k]] : aiVector3D(0.0f, 1.0f, 0.0f);
                vbo.addData(glm::normalize(glm::vec3(normal.x, normal.y, normal.z)));
            }
        }
    }
}

void ModelMesh::clearData() {
    vbo.deleteVBO();
}

std::string ModelMesh::aiStringToStdString(const aiString& aiStringStruct)
{
    auto dataPtr = aiStringStruct.data;
    while (*dataPtr == 0) {
        dataPtr++;
    }

    return dataPtr;
}

void ModelMesh::setVertexAttributesPointers(int numVertices)
{
    uint64_t offset = 0;

    //pos
    glEnableVertexAttribArray(POSITION_ATTRIBUTE_INDEX);
    glVertexAttribPointer(POSITION_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void*>(offset));

    offset += sizeof(glm::vec3)*numVertices;

    //uvs
    glEnableVertexAttribArray(TEXTURE_COORDINATE_ATTRIBUTE_INDEX);
    glVertexAttribPointer(TEXTURE_COORDINATE_ATTRIBUTE_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), reinterpret_cast<void*>(offset));

    offset += sizeof(glm::vec2)*numVertices;

    //normals
    glEnableVertexAttribArray(NORMAL_ATTRIBUTE_INDEX);
    glVertexAttribPointer(NORMAL_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void*>(offset));

    offset += sizeof(glm::vec3)*numVertices;
}

void ModelMesh::render() const
{
    if (!isInitialized) {
        return;
    }

    glBindVertexArray(vao_ind);

    std::string lastUsedTextureKey = "";
    for(auto i = 0; i < _meshStartIndices.size(); i++)
    {
        const auto usedMaterialIndex = _meshMaterialIndices[i];
        if (_materialTextureKeys.count(usedMaterialIndex) > 0)
        {
            const auto textureKey = _materialTextureKeys.at(usedMaterialIndex);
            if (textureKey != lastUsedTextureKey) {
                TextureManager::getInstance().getTexture(textureKey).bind();
            }
        }

        glDrawArrays(GL_TRIANGLES, _meshStartIndices[i], _meshVerticesCount[i]);
    }
}

ModelMesh::~ModelMesh() {
    clearData();
}

void ModelMesh::loadMaterialTexture(const int materialIndex, const std::string &textureFileName) {
    // If the texture with such path is already loaded, just use it and go on
    const auto fullTexturePath = PathHelper::GetFullTexturePath(textureFileName);
    const auto newTextureKey = "assimp_" + fullTexturePath;

    const auto contains = TextureManager::getInstance().containsTexture(newTextureKey);
    if (!contains) {
        TextureManager::getInstance().loadTexture2D(newTextureKey, fullTexturePath);
    }

    _materialTextureKeys[materialIndex] = newTextureKey;
}


