#include "RenderBuff.h"
#include <iostream>
RenderBuff::~RenderBuff() {
    if (m_renderBufferID == 0) {
        return;
    }
    std::cout << "Deleting renderbuffer with ID " << m_renderBufferID << std::endl;
    glDeleteRenderbuffers(1, &m_renderBufferID);
    m_renderBufferID = 0;
    m_width = 0;
    m_height = 0;
    m_depth = -1;
    m_stencil = -1;
}

bool RenderBuff::create(GLenum format, GLsizei width, GLsizei height) {
    glGenRenderbuffers(1, &m_renderBufferID);
    if (m_renderBufferID == 0)
    {
        std::cerr << "Unable to create renderbuffer with internal format " << m_format << "with width: " << width << "and height: " << height << std::endl;
        return false;
    }

    std::cout << "Created renderbuffer with ID " << m_renderBufferID << std::endl;
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferID);
    glRenderbufferStorage(GL_RENDERBUFFER, m_format, width, height);
    m_format = m_format;
    m_width = width;
    m_height = height;

    return true;
}

bool RenderBuff::resize(GLsizei width, GLsizei height) {
    if (m_renderBufferID == 0) {
        return false;
    }
    const auto internalFormat = m_format;
    deleteRenderBuff();
    return create(internalFormat, width, height);
}

GLuint RenderBuff::getID() const
{
    return m_renderBufferID;
}

void RenderBuff::deleteRenderBuff() {
    if (m_renderBufferID == 0) {
        return;
    }
    std::cout << "Deleting renderbuffer with ID " << m_renderBufferID << std::endl;
    glDeleteRenderbuffers(1, &m_renderBufferID);
    m_renderBufferID = 0;
    m_width = 0;
    m_height = 0;
    m_depth = -1;
    m_stencil = -1;
}
