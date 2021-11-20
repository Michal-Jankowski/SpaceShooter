#pragma once
#include "StaticMeshIndexed3D.h"
#include "GLAD/glad.h"
class Sphere : public StaticMeshIndexed3D
{
public:
    Sphere(float radius, int numSlices, int numStacks, bool withPositions = true, bool withTextureCoordinates = true, bool withNormals = true);

    void render() const override;
    void renderPoints() const override;
    float getRadius() const;
    int getNumSlices() const;
    int getNumStacks() const;

private:
    float m_radius; // Sphere radius
    int m_numSlices; // Number of slices
    int m_numStacks; // Number of stacks

    GLuint m_numPoleIndices; // Number of indices to render poles with GL_TRIANGLES
    GLuint m_numBodyIndices; // Number of indices to render body

    GLuint m_northPoleIndexOffset; // Index offset to render north pole (always 0)
    GLuint m_bodyIndexOffset; // Index offset to render body
    GLuint m_southPoleIndexOffset; // Index offset to render south pole

    void initializeData() override;
};

