#include <iostream>
#include "UniformBufferObject.h"

UniformBufferObject::~UniformBufferObject()
{
	deleteUBO();
}

void UniformBufferObject::createUBO(const size_t byteSize, GLenum usageHint)
{
	if (m_isBufferCreated) {
		std::cerr << "This UBO is already created!" << std::endl;
	}
	//gen buffer ID, then immediate bind and reserve space
	glGenBuffers(1, &m_bufferID);
	glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
	glBufferData(GL_UNIFORM_BUFFER, byteSize, NULL, usageHint);

	// Mark that the buffer has been created and store its size
	m_isBufferCreated = true;
	m_bytesSize = byteSize;

}

void UniformBufferObject::bindUBO() const
{
	if (!m_isBufferCreated)
	{
		std::cerr << "UBO is not created yet! You cannot bind it before you create it!" << std::endl;
		return;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, m_bufferID);
}

void UniformBufferObject::setBufferData(const size_t offset, const void* ptrData, const size_t dataSize)
{
	if (!m_isBufferCreated)
	{
		std::cerr << "Could not set data because uniform buffer object is not created yet!" << std::endl;
		return;
	}

	if (offset >= m_bytesSize)
	{
		std::cerr << "Tried to set data of uniform buffer object at offset " << offset << ", but it's beyond buffer size " << m_bytesSize << ", will be ignored..." << std::endl;
		return;
	}

	if (offset + dataSize > m_bytesSize)
	{
		std::cerr << "Could not set data because it would overflow the buffer! Offset: " << offset << ", data size: " << dataSize << std::endl;
		return;
	}
	glBufferSubData(GL_UNIFORM_BUFFER, offset, dataSize, ptrData);

}

void UniformBufferObject::bindBufferBaseToBindingPoint(const GLuint bindingPoint)
{
	if (!m_isBufferCreated) {
		std::cerr << "Could not bind buffer base to binding point" << bindingPoint << ", because UBO is not created yet!" << std::endl;
		return;
	}
	glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, m_bufferID);
}

GLuint UniformBufferObject::getBufferID() const
{
	return m_bufferID;
}

void UniformBufferObject::deleteUBO()
{
	if (!m_isBufferCreated) {
		return;
	}
	std::cout << "Deleting uniform buffer object with ID " << m_bufferID << "..." << std::endl;
	glDeleteBuffers(1, &m_bufferID);
	m_isBufferCreated = false;
}
