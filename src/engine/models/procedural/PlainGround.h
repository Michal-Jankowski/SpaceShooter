#pragma once
#include <glm/glm.hpp>
#include "../../utils/Buffer.h"
class PlainGround
{
public:
	PlainGround(bool withPosition = true, bool withTextureCoords = true, bool withNormals = true);
	~PlainGround();

	static const int POSITION_ATTRIBUTE_INDEX; // Vertex attribute index of vertex position (0)
	static const int TEXTURE_COORDINATE_ATTRIBUTE_INDEX; // Vertex attribute index of texture coordinate (1)
	static const int NORMAL_ATTRIBUTE_INDEX; // Vertex attribute index of vertex normal (2)
	static glm::vec3 m_vertices[4]; //vertices mesh
	static glm::vec2 m_textureCoords[4]; // coords mesh
	void render() const;
private:
	void initData();
	void deleteMesh();
	void setVertexAttributesPointers(int numVertices);
	int getVertexByteSize() const;
	bool m_hasPositions = false; // Flag telling, if we have vertex positions
	bool m_hasTextureCoordinates = false; // Flag telling, if we have texture coordinates
	bool m_hasNormals = false; // Flag telling, if we have vertex normals

	bool m_isInitialized = false; // Is mesh initialized flag
	GLuint m_vao = 0; // VAO ID from OpenGL
	Buffer m_vbo; // Our VBO wrapper class holding static mesh data
};

