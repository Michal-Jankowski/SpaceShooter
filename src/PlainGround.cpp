#include "PlainGround.h"
#include "ShaderProgramManager.h"

glm::vec3 PlainGround::m_vertices[4] =
{
    glm::vec3(-200.0f, 0.0f, -200.0f), // Left-back point
    glm::vec3(-200.0f, 0.0f, 200.0f), // Left-front point
    glm::vec3(200.0f, 0.0f, -200.0f), // Right-back point
    glm::vec3(200.0f, 0.0f, 200.0f) // Right-front point
};

glm::vec2 PlainGround::m_textureCoords[4] =
{
    glm::vec2(0.0f, 20.0f),
    glm::vec2(0.0f, 0.0f),
    glm::vec2(20.0f, 20.0f),
    glm::vec2(20.0f, 0.0f)
};

const int PlainGround::POSITION_ATTRIBUTE_INDEX = 0;
const int PlainGround::TEXTURE_COORDINATE_ATTRIBUTE_INDEX = 1;
const int PlainGround::NORMAL_ATTRIBUTE_INDEX = 2;


PlainGround::PlainGround(bool withPositions, bool withTextureCoordinates, bool withNormals) 
    : m_hasPositions(withPositions)
    , m_hasTextureCoordinates(withTextureCoordinates)
    , m_hasNormals(withNormals)
{
    initData();
}

PlainGround::~PlainGround() {
    deleteMesh();
}


void PlainGround::render() const
{
    if (!m_isInitialized) {
        return;
    }

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

int PlainGround::getVertexByteSize() const
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

void PlainGround::deleteMesh() {
    if (!m_isInitialized) {
        std::cout << "Trying to delete unitialized mesh!";
        return;
    }
    glDeleteVertexArrays(1, &m_vao);
    m_vbo.deleteVBO();
    m_isInitialized = false;
}

void PlainGround::setVertexAttributesPointers(int numVertices) {
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


void PlainGround::initData()
{
    if (m_isInitialized) {
        return;
    }

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    const auto numVertices = 4;
    const auto vertexByteSize = getVertexByteSize();
    m_vbo.createVBO(vertexByteSize * numVertices);
    m_vbo.bindVBO();

    if (m_hasPositions) {
        m_vbo.addRawData(m_vertices, sizeof(glm::vec3) * numVertices);
    }

    if (m_hasTextureCoordinates) {
        m_vbo.addRawData(m_textureCoords, sizeof(glm::vec2) * numVertices);
    }

    if (m_hasNormals) {
        glm::vec3 normal(0.0f, 1.0f, 0.0f);
        m_vbo.addRawData(&normal, sizeof(glm::vec3), numVertices);
    }

    m_vbo.uploadDataToGPU(GL_STATIC_DRAW);
    setVertexAttributesPointers(numVertices);
    m_isInitialized = true;
}

