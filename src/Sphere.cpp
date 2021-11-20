#include "Sphere.h"
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>
Sphere::Sphere(float radius, int numSlices, int numStacks, bool withPositions, bool withTextureCoordinates, bool withNormals)
    : StaticMeshIndexed3D(withPositions, withTextureCoordinates, withNormals)
    , m_radius(radius)
    , m_numSlices(numSlices)
    , m_numStacks(numStacks)
{
    // Validate input by throwing an exception - such spheres don't even make any sense
    if (numSlices < 3 || numStacks < 2) {
        throw std::runtime_error("Sphere cannot have less than 3 slices and less than 2 stacks!");
    }

    initializeData();
}

void Sphere::render() const
{
    if (!m_isInit) {
        return;
    }

    glBindVertexArray(m_vao);

    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(m_primitiveRestartIndex);

    // Render north pole
    glDrawElements(GL_TRIANGLES, m_numPoleIndices, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * m_northPoleIndexOffset));

    // Render body
    glDrawElements(GL_TRIANGLE_STRIP, m_numBodyIndices, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * m_bodyIndexOffset));

    // Render south pole 
    glDrawElements(GL_TRIANGLES, m_numPoleIndices, GL_UNSIGNED_INT, (void*)(sizeof(GLuint) * m_southPoleIndexOffset));

    // Disable primitive restart, we won't need it now
    glDisable(GL_PRIMITIVE_RESTART);
}

void Sphere::renderPoints() const
{
    if (!m_isInit) {
        return;
    }

    glBindVertexArray(m_vao);
    glDrawArrays(GL_POINTS, 0, m_numVertices);
}

float Sphere::getRadius() const
{
    return m_radius;
}

int Sphere::getNumSlices() const
{
    return m_numSlices;
}

int Sphere::getNumStacks() const
{
    return m_numStacks;
}

void Sphere::initializeData()
{
    if (m_isInit) {
        return;
    }

    // Cache count of vertices
    m_numVertices = (m_numStacks + 1) * (m_numSlices + 1);

    // Cache number of indices it takes to render body
    const auto numBodyStacks = m_numStacks - 2;
    const auto numBodyPrimitiveRestarts = std::max(0, numBodyStacks - 1);
    m_numBodyIndices = 2 * numBodyStacks * (m_numSlices + 1) + numBodyPrimitiveRestarts;

    // Cache count of pole indices
    m_numPoleIndices = m_numSlices * 3;

    // Cache offsets for sphere parts
    m_northPoleIndexOffset = 0;
    m_bodyIndexOffset = m_numPoleIndices;
    m_southPoleIndexOffset = m_bodyIndexOffset + m_numBodyIndices;

    // Finally cache total number of indices and primitive restart index
    m_numIndices = 2 * m_numPoleIndices + m_numBodyIndices;
    m_primitiveRestartIndex = m_numVertices;

    // Generate VAO and VBOs for vertex attributes and indices
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    m_vbo.createVBO(getVertexByteSize() * m_numVertices);
    m_indicesVBO.createVBO(sizeof(GLuint) * m_numIndices);

    // Pre-calculate sines / cosines for given number of slices
    const auto sliceAngleStep = 2.0f * glm::pi<float>() / static_cast<float>(m_numSlices);
    auto currentSliceAngle = 0.0f;
    std::vector<float> sliceSines, sliceCosines;
    for (auto i = 0; i <= m_numSlices; i++)
    {
        sliceSines.push_back(sin(currentSliceAngle));
        sliceCosines.push_back(cos(currentSliceAngle));

        // Update slice angle
        currentSliceAngle += sliceAngleStep;
    }

    // Pre-calculate sines / cosines for given number of stacks
    const auto stackAngleStep = -glm::pi<float>() / static_cast<float>(m_numStacks);
    auto currentStackAngle = glm::pi<float>() / 2.0f;
    std::vector<float> stackSines, stackCosines;
    for (auto i = 0; i <= m_numStacks; i++)
    {
        stackSines.push_back(sin(currentStackAngle));
        stackCosines.push_back(cos(currentStackAngle));

        // Update stack angle
        currentStackAngle += stackAngleStep;
    }

    // Generate sphere vertex positions
    if (hasPositions())
    {
        for (auto i = 0; i <= m_numStacks; i++)
        {
            for (auto j = 0; j <= m_numSlices; j++)
            {
                const auto x = m_radius * stackCosines[i] * sliceCosines[j];
                const auto y = m_radius * stackSines[i];
                const auto z = m_radius * stackCosines[i] * sliceSines[j];
                m_vbo.addData(glm::vec3(x, y, z));
            }
        }
    }

    // Generate sphere texture coordinates
    if (hasTextureCoordinates())
    {
        for (auto i = 0; i <= m_numStacks; i++)
        {
            for (auto j = 0; j <= m_numSlices; j++)
            {
                const auto x = stackCosines[i] * sliceCosines[j];
                const auto y = stackSines[i];
                const auto z = stackCosines[i] * sliceSines[j];

                // There are many options out there to generate sphere texture coordinates
                // I have commented out some others here that work, some better, some worse
                // You can try them all out :)

                // float u = atan2(x, z) / (2.0f * glm::pi<float>());
                // float v = asin(y) / glm::pi<float>();

                // float u = 0.5f + asin(x) / glm::pi<float>();
                // float v = 0.5f + asin(y) / glm::pi<float>();

                // float u = 0.5f + x * 0.5f;
                // float v = 0.5f + y * 0.5f;

                const auto u = 1.0f - static_cast<float>(j) / m_numSlices;
                const auto v = 1.0f - static_cast<float>(i) / m_numStacks;
                m_vbo.addData(glm::vec2(u, v));
            }
        }
    }

    // Generate sphere normals
    if (hasNormals())
    {
        for (auto i = 0; i <= m_numStacks; i++)
        {
            for (auto j = 0; j <= m_numSlices; j++)
            {
                const auto x = stackCosines[i] * sliceCosines[j];
                const auto y = stackSines[i];
                const auto z = stackCosines[i] * sliceSines[j];
                m_vbo.addData(glm::vec3(x, y, z));
            }
        }
    }

    // Now that we have all vertex data, generate indices for north pole (triangles)
    for (auto i = 0; i < m_numSlices; i++)
    {
        GLuint sliceIndex = i;
        GLuint nextSliceIndex = sliceIndex + m_numSlices + 1;
        m_indicesVBO.addData(static_cast<GLuint>(sliceIndex));
        m_indicesVBO.addData(static_cast<GLuint>(nextSliceIndex));
        m_indicesVBO.addData(static_cast<GLuint>(nextSliceIndex + 1));
    }

    // Then for body (triangle strip)
    GLuint currentVertexIndex = m_numSlices + 1;
    for (auto i = 0; i < numBodyStacks; i++)
    {
        // Primitive restart triangle strip from second body stack on
        if (i > 0)
        {
            m_indicesVBO.addData(m_primitiveRestartIndex);
        }

        for (auto j = 0; j <= m_numSlices; j++)
        {
            GLuint sliceIndex = currentVertexIndex + j;
            GLuint nextSliceIndex = currentVertexIndex + m_numSlices + 1 + j;
            m_indicesVBO.addData(sliceIndex);
            m_indicesVBO.addData(nextSliceIndex);
        }

        currentVertexIndex += m_numSlices + 1;
    }

    // And finally south pole (triangles again)
    GLuint beforeLastStackIndexOffset = m_numVertices - 2 * (m_numSlices + 1);
    for (auto i = 0; i < m_numSlices; i++)
    {
        GLuint sliceIndex = beforeLastStackIndexOffset + i;
        GLuint nextSliceIndex = sliceIndex + m_numSlices + 1;
        m_indicesVBO.addData(static_cast<GLuint>(sliceIndex));
        m_indicesVBO.addData(static_cast<GLuint>(sliceIndex + 1));
        m_indicesVBO.addData(static_cast<GLuint>(nextSliceIndex));
    }

    m_vbo.bindVBO();
    m_vbo.uploadDataToGPU(GL_STATIC_DRAW);
    setVertexAttributesPointers(m_numVertices);

    m_indicesVBO.bindVBO(GL_ELEMENT_ARRAY_BUFFER);
    m_indicesVBO.uploadDataToGPU(GL_STATIC_DRAW);

    m_isInit = true;
}
