#pragma once

#include <GLAD/glad.h>

class UniformBufferObject
{
public:
	~UniformBufferObject();

	void createUBO(const size_t byteSize, GLenum usageHint = GL_STREAM_DRAW);
	void bindUBO() const;
	void setBufferData(const size_t offset, const void* ptrData, const size_t dataSize);
	void bindBufferBaseToBindingPoint(const GLuint bindingPoints);
	GLuint getBufferID() const;
	void deleteUBO();
private:
	GLuint m_bufferID{ 0 };
	size_t m_bytesSize;
	bool m_isBufferCreated = false;
}; 

class UniformBlockBindingPoints
{
public:
	static const int MATRICES{ 0 };
	static const int POINT_LIGHTS{ 1 };
};

