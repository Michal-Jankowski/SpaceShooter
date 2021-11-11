#pragma once

#include <GLAD/glad.h>

class Sphere
{
public:
	Sphere(float radius, int slices, bool withPosition = true, bool withTexCoords = true, bool withnormals = true);
	~Sphere();
	void render();
	void renderPoints();
	void deleteMesh();
private:
	float m_radius;
	int m_numSlices, m_numStackes;
	GLuint m_numPoleIndices, m_numBodyIndices;
	GLuint m_nortPoleIndexOffset, m_southPoleIndexOffset, m_bodyIndexOffset;
	int m_numVertices = 0, m_numIndices = 0, m_primitiveRestartIndex = 0;
	void initData();
};

