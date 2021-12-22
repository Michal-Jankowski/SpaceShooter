#pragma once
#include "../../utils/Buffer.h"
class StaticMesh3D
{
public:
	static const int POSITION_ATTRIBUTE_INDEX; // Vertex attribute index of vertex position (0)
	static const int TEXTURE_COORDINATE_ATTRIBUTE_INDEX; // Vertex attribute index of texture coordinate (1)
	static const int NORMAL_ATTRIBUTE_INDEX; // Vertex attribute index of vertex normal (2)

	StaticMesh3D(bool withPositions, bool withTextureCoordinates, bool withNormals);
	virtual ~StaticMesh3D();
	virtual void render() const = 0;
	virtual void renderPoints() const {}
	virtual void deleteMesh();
	bool hasPositions() const;
	bool hasTextureCoordinates() const;
	bool hasNormals() const;
	int getVertexByteSize() const;

protected:
	bool m_hasPositions = false; 
	bool m_hasTexCoords = false; 
	bool m_hasNormals = false; 

	bool m_isInit = false;
	GLuint m_vao = 0; 
	Buffer m_vbo; 
	virtual void initializeData() {}
	void setVertexAttributesPointers(int numVertices);
};
