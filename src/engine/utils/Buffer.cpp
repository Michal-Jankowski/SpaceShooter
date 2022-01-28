#include "Buffer.h"
#include <iostream>
#include <cstring>

void Buffer::create(size_t reserveBytes) {

	if (m_isReady) {
		std::cerr << "ERROR: Buffer already initialized!" << std::endl;
		return;
	}

	glGenBuffers(1, &m_bufferID);
	m_rawData.reserve(reserveBytes > 0 ? reserveBytes : 512 * 4);
	m_isReady = true;
}

void Buffer::bind(GLenum bufferType) {
	if (!m_isReady) {
		std::cerr << "ERROR: This buffer is not initialized yet!" << std::endl;
		return;
	}
	m_bufferType = bufferType;
	glBindBuffer(m_bufferType, m_bufferID);
}

void Buffer::addData(const void* data, size_t size, int repeat) {
    const auto bytesToAdd = size * repeat;
    const auto requiredCapacity = m_bytesAdded + bytesToAdd;
    const auto resizeStep = 3;
    if (requiredCapacity > m_rawData.capacity()) {
        auto newCapacity = m_rawData.capacity() * resizeStep;

        while (newCapacity < requiredCapacity) {
            newCapacity *= resizeStep;
        }
        std::vector<unsigned char> tmpNewData;
        tmpNewData.reserve(newCapacity);
        auto dataPtr = std::data(tmpNewData);
        auto tmpDataPtr = std::data(m_rawData);
        //mecpy do: m_rawData.data() z: data, o: dataSize
        memcpy(dataPtr, tmpDataPtr, m_bytesAdded);
        m_rawData = std::move(tmpNewData);
    }
    for (int i = 0; i < repeat; i++) {
        auto dataPtr = std::data(m_rawData);
        auto ptrOffset = dataPtr + m_bytesAdded;
        //mecpy do: m_rawData.data() + m_bytesAdded z: data, o: dataSize
        memcpy(ptrOffset, data, size);
        m_bytesAdded += size;
    }
}

void Buffer::upload(GLenum usageHint) {
    if (!m_isReady) {
        std::cerr << "ERROR: Create buffer first" << std::endl;
        return;
    }
    glBufferData(m_bufferType, m_bytesAdded, m_rawData.data(), usageHint);
    m_isLoaded = true;
    m_uploadedDataSize = m_bytesAdded;
    m_bytesAdded = 0;
}

void Buffer::deleteBuffer() {
    if (!m_isReady) {
        return;
    }
    glDeleteBuffers(1, &m_bufferID);
    m_isLoaded = false;
    m_isReady = false;
}

