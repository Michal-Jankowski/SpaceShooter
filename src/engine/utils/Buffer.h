#pragma once

#include <vector>
#include <GLAD/glad.h>

#ifndef SPACESHOOTER_BUFFER_H
#define SPACESHOOTER_BUFFER_H

class Buffer
{
public:
	void create(size_t reserveBytes = 0);
	void deleteBuffer();
	void bind(GLenum bufferType = GL_ARRAY_BUFFER);
	void addRawData(const void* data, size_t dataSizeinBytes, int repeat = 1);
	void upload(GLenum usageHint);
	GLuint m_bufferID{ 0 };

	template<typename T>
	void addData(const T& ptrObj, int repeat = 1)
	{
		addRawData(&ptrObj, sizeof(T), repeat);
	}
private:
	std::vector<unsigned char> m_rawData;
	size_t m_bytesAdded{ 0 };
	size_t m_uploadedDataSize;
	int m_bufferType{ 0 };
	bool m_isReady = false;
	bool m_isLoaded = false;
};

#endif //SPACESHOOTER_BUFFER_H