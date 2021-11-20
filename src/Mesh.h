#pragma once
#include <GLAD/glad.h>
#include "Buffer.h"
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
	bool hasPositions() const;
	bool hasTextureCoordinates() const;
	bool hasNormals() const;
	int getVertexByteSize() const;
protected:
	bool _hasPositions = false; 
	bool _hasTextureCoordinates = false; 
	bool _hasNormals = false; 

	bool _isInitialized = false; 
	GLuint _vao = 0; 
	Buffer _vbo; 

	virtual void initializeData() {}
	void setVertexAttributesPointers(int numVertices);

};

