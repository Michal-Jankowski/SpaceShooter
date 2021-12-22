#include "Buffer.h"
#include <iostream>
#include <cstring>

void Buffer::createVBO(size_t reserveBytes) {

	if (m_isBufferInitalized) {
		std::cerr << "Buffer already initialized! You need to delete it before re-initailizing it!" << std::endl;
		return;
	}

	glGenBuffers(1, &m_bufferID);
	m_rawData.reserve(reserveBytes > 0 ? reserveBytes : 1024);
	std::cout << "Created buffer with ID " << m_bufferID << " and reserved size of " << m_rawData.capacity() << "bytes" << std::endl;
	m_isBufferInitalized = true;
}

void Buffer::bindVBO(GLenum bufferType) {
	if (!m_isBufferInitalized) {
		std::cerr << "This buffer is not initialized yet! You need to create it first!" << std::endl;
		return;
	}
	m_bufferType = bufferType;
	glBindBuffer(m_bufferType, m_bufferID);
}

void Buffer::addRawData(const void* data, size_t dataSize, int repeat) {

    const auto bytesToAdd = dataSize * repeat;
    const auto requiredCapacity = m_bytesAdded + bytesToAdd;
    // resize the rawData vector, default to two times the default capacity
    if (requiredCapacity > m_rawData.capacity()) {
        auto newCapacity = m_rawData.capacity() * 2;

        while (newCapacity < requiredCapacity) {
            newCapacity *= 2;
        }
        std::vector<unsigned char> newRawData;
        newRawData.reserve(newCapacity);
        memcpy(newRawData.data(), m_rawData.data(), m_bytesAdded);
        m_rawData = std::move(newRawData);
    }
    for (int i = 0; i < repeat; i++) {
        memcpy(m_rawData.data() + m_bytesAdded, data, dataSize);
        m_bytesAdded += dataSize;
    }
}

void Buffer::uploadDataToGPU(GLenum usageHint) {
    if (!m_isBufferInitalized)
    {
        std::cerr << "This buffer is not initialized yet! You shall call createVBO before sending to GPU!" << std::endl;
        return;
    }
    glBufferData(m_bufferType, m_bytesAdded, m_rawData.data(), usageHint);
    m_isDataLoaded = true;
    m_uploadedDataSize = m_bytesAdded;
    m_bytesAdded = 0;
}

void Buffer::deleteVBO() {
    if (!m_isBufferInitalized) {
        return;
    }
    std::cout << "Delete VBO with ID" << m_bufferID << std::endl;
    glDeleteBuffers(1, &m_bufferID);
    m_isDataLoaded = false;
    m_isBufferInitalized = false;
}

