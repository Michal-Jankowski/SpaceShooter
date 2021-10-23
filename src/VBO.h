#pragma once

#include <vector>
#include <GLAD/glad.h>
class VBO
{
public:
	void createVBO(size_t reserveBytes = 0);
	void deleteVBO();
	void bindVBO(GLenum bufferType = GL_ARRAY_BUFFER);
	void addRawData(const void* data, size_t dataSizeinBytes, int repeat = 1);
	void uploadDataToGPU(GLenum usageHint);

	template<typename T>
	void addData(const T& ptrObj, int repeat = 1)
	{
		addRawData(&ptrObj, sizeof(T), repeat);
	}
private:
	GLuint m_bufferID = 0;
	std::vector<unsigned char> m_rawData;
	size_t m_bytesAdded = 0;
	size_t m_uploadedDataSize;
	int m_bufferType;
	bool m_isBufferInitalized = false;
	bool m_isDataLoaded = false;
};

