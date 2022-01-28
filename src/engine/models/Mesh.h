#pragma once
#include <GLAD/glad.h>
#include "../utils/Buffer.h"
class Mesh
{
public:
	static const int POSITION_ATTRIBUTE_INDEX; 
	static const int TEXTURE_COORDINATE_ATTRIBUTE_INDEX; 
	static const int NORMAL_ATTRIBUTE_INDEX; 

	Mesh(bool withPositions, bool withTextureCoordinates, bool withNormals);
	virtual ~Mesh();

	virtual void render() const = 0;
	virtual void renderPoints() const {}
	virtual void deleteMesh();

protected:
	bool m_hasPositions = false; 
	bool m_hasTextureCoordinates = false; 
	bool m_hasNormals = false; 

	bool m_isInitialized = false; 
	GLuint m_vao = 0; 
	Buffer m_vbo; 

	virtual void initializeData() {}
	void setVertexAttributesPointers(int numVertices);

};

