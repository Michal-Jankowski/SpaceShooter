#include "Cube.h"
#include <glm/glm.hpp>
#include <iostream>

    glm::vec3 Cube::vertices[36] = {
        // Front face
        glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f),
        // Back face
        glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f),
        // Left face
        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),
        // Right face
        glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f),
        // Top face
        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),
        // Bottom face
        glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 0.5f),
    };

    glm::vec2 Cube::textureCoordinates[6] = {
        glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 1.0f)
    };

    glm::vec3 Cube::normals[6] = {
        glm::vec3(0.0f, 0.0f, 1.0f), // Front face
        glm::vec3(0.0f, 0.0f, -1.0f), // Back face
        glm::vec3(-1.0f, 0.0f, 0.0f), // Left face
        glm::vec3(1.0f, 0.0f, 0.0f), // Right face
        glm::vec3(0.0f, 1.0f, 0.0f), // Top face
        glm::vec3(0.0f, -1.0f, 0.0f), // Bottom face
    };

    const int Cube::POSITION_ATTRIBUTE_INDEX = 0;
    const int Cube::TEXTURE_COORDINATE_ATTRIBUTE_INDEX = 1;
    const int Cube::NORMAL_ATTRIBUTE_INDEX = 2;

    Cube::Cube(bool withPositions, bool withTextureCoordinates, bool withNormals)
    {
        initializeData();
    }

    Cube::~Cube() {
        deleteMesh();
    }

    void Cube::render() const
    {
        if (!m_isInitialized) {
            return;
        }

        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void Cube::renderPoints() const
    {
        if (!m_isInitialized) {
            return;
        }

        glBindVertexArray(m_vao);
        glDrawArrays(GL_POINTS, 0, 36);
    }

    void Cube::renderFaces(int facesBitmask) const
    {
        if (!m_isInitialized) {
            return;
        }

        glBindVertexArray(m_vao);

        if (facesBitmask & CUBE_FRONT_FACE) {
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        if (facesBitmask & CUBE_BACK_FACE) {
            glDrawArrays(GL_TRIANGLES, 6, 6);
        }
        if (facesBitmask & CUBE_LEFT_FACE) {
            glDrawArrays(GL_TRIANGLES, 12, 6);
        }
        if (facesBitmask & CUBE_RIGHT_FACE) {
            glDrawArrays(GL_TRIANGLES, 18, 6);
        }
        if (facesBitmask & CUBE_TOP_FACE) {
            glDrawArrays(GL_TRIANGLES, 24, 6);
        }
        if (facesBitmask & CUBE_BOTTOM_FACE) {
            glDrawArrays(GL_TRIANGLES, 30, 6);
        }
    }

    void Cube::initializeData()
    {
        if (m_isInitialized) {
            return;
        }

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        const auto numVertices = 36;
        const auto vertexByteSize = getVertexByteSize();
        m_vbo.createVBO(vertexByteSize * numVertices);
        m_vbo.bindVBO();

        if (m_hasPositions) {
            m_vbo.addRawData(vertices, sizeof(glm::vec3) * numVertices);
        }

        if (m_hasTextureCoordinates) {
            for (auto i = 0; i < 6; i++) {
                m_vbo.addRawData(textureCoordinates, sizeof(glm::vec2) * 6);
            }
        }

        if (m_hasNormals) {
            for (auto i = 0; i < 6; i++) {
                m_vbo.addRawData(&normals[i], sizeof(glm::vec3), 6);
            }
        }

        m_vbo.uploadDataToGPU(GL_STATIC_DRAW);
        setVertexAttributesPointers(numVertices);
        m_isInitialized = true;
    }

    void Cube::deleteMesh() {
        if (!m_isInitialized) {
            std::cout << "Trying to delete unitialized mesh!";
            return;
        }
        glDeleteVertexArrays(1, &m_vao);
        m_vbo.deleteVBO();
        m_isInitialized = false;
    }

    int Cube::getVertexByteSize() const
    {
        int result = 0;
        if (m_hasPositions) {
            result += sizeof(glm::vec3);
        }
        if (m_hasTextureCoordinates) {
            result += sizeof(glm::vec2);
        }
        if (m_hasNormals) {
            result += sizeof(glm::vec3);
        }
        return result;
    }

    void Cube::setVertexAttributesPointers(int numVertices) {
        uint64_t offset = 0;
        if (m_hasPositions) {
            glEnableVertexAttribArray(POSITION_ATTRIBUTE_INDEX);
            glVertexAttribPointer(POSITION_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void*>(offset));

            offset += sizeof(glm::vec3) * numVertices;
        }

        if (m_hasTextureCoordinates) {
            glEnableVertexAttribArray(TEXTURE_COORDINATE_ATTRIBUTE_INDEX);
            glVertexAttribPointer(TEXTURE_COORDINATE_ATTRIBUTE_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), reinterpret_cast<void*>(offset));

            offset += sizeof(glm::vec2) * numVertices;
        }

        if (m_hasNormals) {
            glEnableVertexAttribArray(NORMAL_ATTRIBUTE_INDEX);
            glVertexAttribPointer(NORMAL_ATTRIBUTE_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void*>(offset));

            offset += sizeof(glm::vec3) * numVertices;
        }
    }

