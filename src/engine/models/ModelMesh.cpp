#include "ModelMesh.h"
#include "../textures/TextureManager.h"
#include "../utils/PathHelper.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <GLAD/glad.h>

const int ModelMesh::POSITION_ATTRIBUTE_INDEX           = 0;
const int ModelMesh::TEXTURE_COORDINATE_ATTRIBUTE_INDEX = 1;
const int ModelMesh::NORMAL_ATTRIBUTE_INDEX             = 2;
const int ModelMesh::TANGENT_ATTRIBUTE_INDEX            = 3;
const int ModelMesh::BITANGENT_ATTRIBUTE_INDEX          = 4;


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

    glGenVertexArrays(1, &m_vao_ind);
    glBindVertexArray(m_vao_ind);

    m_vbo.create();
    m_vbo.bind(GL_ARRAY_BUFFER);

    //vert pos, vert normal, uv coord
    const int vertSize = sizeof(aiVector3D) * 2 + sizeof(aiVector2D);

    int vertexCount = ReadMeshPositions(scene);
    ReadMeshUVs(scene);
    ReadMeshNormals(scene);
    ReadMeshMaterials(scene);

    m_vbo.upload(GL_STATIC_DRAW);
    setVertexAttributesPointers(vertexCount);
    isInitialized = true;

    return isInitialized;
}

void ModelMesh::ReadMeshMaterials(const aiScene *scene) {
    for(size_t i = 0; i < scene->mNumMaterials; i++)
    {
        const auto materialPtr = scene->mMaterials[i];
        auto m = std::make_unique<Material>(materialPtr);
        materials[static_cast<int>(i)] = std::move(m);
    }
}

int ModelMesh::ReadMeshPositions(const aiScene *scene) {
    auto vertexCount = 0;
    for (size_t i = 0; i < scene->mNumMeshes; i++)
    {
        const auto meshPtr = scene->mMeshes[i];
        auto vertexCountMesh = 0;
        m_meshStartIndices.push_back(vertexCount);
        m_meshMaterialIndices.push_back(meshPtr->mMaterialIndex);

        for (size_t j = 0; j < meshPtr->mNumFaces; j++)
        {
            const auto& face = meshPtr->mFaces[j];
            if (face.mNumIndices != 3) {
                continue; 
            }

            for (size_t k = 0; k < face.mNumIndices; k++)
            {
                const auto& position = meshPtr->mVertices[face.mIndices[k]];
                const auto data = glm::vec3(position.x, position.y, position.z);
                m_vbo.addData(&data, sizeof(data));
            }

            vertexCountMesh += face.mNumIndices;
        }

        vertexCount += vertexCountMesh;
        m_meshVerticesCount.push_back(vertexCountMesh);
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
                continue; 
            }

            for (size_t k = 0; k < face.mNumIndices; k++)
            {
                const auto& textureCoord = meshPtr->mTextureCoords[0][face.mIndices[k]];
                m_vbo.addData(&textureCoord, sizeof(aiVector2D));
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
                continue; 
            }

            for (size_t k = 0; k < face.mNumIndices; k++)
            {
                const auto& normal = meshPtr->HasNormals() ? meshPtr->mNormals[face.mIndices[k]] : aiVector3D(0.0f, 1.0f, 0.0f);
                const auto& tangent = meshPtr->HasTangentsAndBitangents() ? meshPtr->mTangents[face.mIndices[k]] : aiVector3D(1.0f, 0.0f, 0.0f);
                const auto& bitangent = meshPtr->HasTangentsAndBitangents() ? meshPtr->mBitangents[face.mIndices[k]] : aiVector3D(0.0f, 0.0f, 1.0f);
                const auto data = glm::normalize(glm::vec3(normal.x, normal.y, normal.z));
                m_vbo.addData(&data, sizeof(data));
            }
        }
    }
    for (size_t i = 0; i < scene->mNumMeshes; i++)
    {
        const auto meshPtr = scene->mMeshes[i];
        for (size_t j = 0; j < meshPtr->mNumFaces; j++)
        {
            const auto& face = meshPtr->mFaces[j];
            if (face.mNumIndices != 3) {
                continue;
            }

            for (size_t k = 0; k < face.mNumIndices; k++)
            {
                const auto& tangent = meshPtr->HasTangentsAndBitangents() ? meshPtr->mTangents[face.mIndices[k]] : aiVector3D(1.0f, 0.0f, 0.0f);
                const auto data = glm::normalize(glm::vec3(tangent.x, tangent.y, tangent.z));
                m_vbo.addData(&data, sizeof(data));
            }
        }
    }
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
                const auto& bitangent = meshPtr->HasTangentsAndBitangents() ? meshPtr->mBitangents[face.mIndices[k]] : aiVector3D(0.0f, 0.0f, 1.0f);
                const auto data = glm::normalize(glm::vec3(bitangent.x, bitangent.y, bitangent.z));
                m_vbo.addData(&data, sizeof(data));
            }
        }
    }
}

void ModelMesh::clearData() {
    m_vbo.deleteBuffer();
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

    glEnableVertexAttribArray(TANGENT_ATTRIBUTE_INDEX);
    glVertexAttribPointer(TANGENT_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void*>(offset));

    offset += sizeof(glm::vec3)*numVertices;

    glEnableVertexAttribArray(BITANGENT_ATTRIBUTE_INDEX);
    glVertexAttribPointer(BITANGENT_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void*>(offset));

    offset += sizeof(glm::vec3)*numVertices;
}

void ModelMesh::render(const glm::mat4 model) const
{
    if (!isInitialized) {
        return;
    }

    glBindVertexArray(m_vao_ind);

    for(auto i = 0; i < m_meshStartIndices.size(); i++)
    {
        const auto usedMaterialIndex = m_meshMaterialIndices[i];
        if (materials.count(usedMaterialIndex) > 0)
        {
            auto mat = *materials.at(usedMaterialIndex);
            mat.setup(model);
            glDrawArrays(GL_TRIANGLES, m_meshStartIndices[i], m_meshVerticesCount[i]);
            if(mat.isTransparent()) {
                glDisable(GL_BLEND);
            }
            glDisable(GL_CULL_FACE);
        }

    }
}

ModelMesh::~ModelMesh() {
    materials.clear();
    clearData();
}

bool ModelMesh::hasTransparentMaterials() {
    for (auto & material : materials){
        if(material.first != NULL && material.second->isTransparent()){
            return true;
        }
    }
    return false;
}


