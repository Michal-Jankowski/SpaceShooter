#include "FrameBuff.h"
#include "../core/SetupWindow.h"
#include "DefaultBuff.h"
#include <iostream>

FrameBuff::~FrameBuff() {
    deleteFrameBuffer();
}

bool FrameBuff::createFrameBufferWithColorAndDepthWithDefaultScreenSize()
{
	const auto screenWidth = SetupWindow::getDefaultWindow()->getScreenWidth();
	const auto screenHeight = SetupWindow::getDefaultWindow()->getScreenHeight();

	return createFrameBufferWithColorAndDepth(screenWidth, screenHeight);
}

bool FrameBuff::createFrameBufferWithColorAndDepth(GLsizei width, GLsizei height)
{
    if (m_frameBufferID != 0) {
        return false;
    }

    // First create and bind framebuffer object (FBO)
    glGenFramebuffers(1, &m_frameBufferID);
    if (m_frameBufferID == 0)
    {
        std::cerr << "Unable to create framebuffer!" << std::endl;
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
    std::cout << "Created framebuffer with ID #" << m_frameBufferID << ", its dimensions will be [" << width << ", " << height << "]" << std::endl;

    // Create color render buffer and attach it to FBO
    auto colorRenderBuffer = std::make_unique<RenderBuff>();
    if (!colorRenderBuffer->create(GL_RGBA8, width, height))
    {
        std::cerr << "Unable to create color attachment for the framebuffer #" << m_frameBufferID << "!" << std::endl;
        deleteFrameBuffer();
        return false;
    }

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderBuffer->getID());

    // Create depth buffer and attach it to FBO
    auto depthRenderBuffer = std::make_unique<RenderBuff>();
    if (!depthRenderBuffer->create(GL_DEPTH_COMPONENT24, width, height))
    {
        std::cerr << "Unable to create depth attachment for the framebuffer #" << m_frameBufferID << "!" << std::endl;
        deleteFrameBuffer();
        return false;
    }

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer->getID());

    // Check FBO status when all attachments have been attached
    const auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Could not attach FBO to create framebuffer #" << m_frameBufferID << "!" << std::endl;
        return false;
    }

    // When everything went well, cache attributes into member variables
    m_colorRenderBuffer = std::move(colorRenderBuffer);
    m_depthRenderBuffer = std::move(depthRenderBuffer);
    m_width = width;
    m_height = height;

    return true;
}

void FrameBuff::bindAsBothReadAndDraw() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);

}

void FrameBuff::bindAsRead() const
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_frameBufferID);

}

void FrameBuff::bindAsDraw() const
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_frameBufferID);

}

bool FrameBuff::resize(GLsizei newWidth, GLsizei newHeight)
{
    if (m_frameBufferID == 0) {
        return false;
    }

    deleteOnlyFrameBuffer();
    // First create and bind framebuffer object (FBO)
    glGenFramebuffers(1, &m_frameBufferID);
    if (m_frameBufferID == 0)
    {
        std::cerr << "Unable to create framebuffer during resizing!" << std::endl;
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
    std::cout << "Resizing framebuffer with ID #" << m_frameBufferID << ", its dimensions will be [" << newWidth << ", " << newHeight << "]" << std::endl;

    if (m_colorRenderBuffer)
    {
        if (!m_colorRenderBuffer->resize(newWidth, newHeight))
        {
            std::cerr << "Unable to resize color attachment for the framebuffer #" << m_frameBufferID << "!" << std::endl;
            deleteFrameBuffer();
            return false;
        }

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorRenderBuffer->getID());
    }

    if (m_depthRenderBuffer)
    {
        if (!m_depthRenderBuffer->resize(newWidth, newHeight))
        {
            std::cerr << "Unable to resize depth attachment for the framebuffer #" << m_frameBufferID << "!" << std::endl;
            deleteFrameBuffer();
            return false;
        }

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderBuffer->getID());
    }

    if (m_texture)
    {
        if (!m_texture->resize(newWidth, newHeight))
        {
            std::cerr << "Unable to resize depth attachment for the framebuffer #" << m_frameBufferID << "!" << std::endl;
            deleteFrameBuffer();
            return false;
        }

        m_texture->bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->getID(), 0);
    }

    // Check FBO status when all attachments have been attached
    const auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
        return false;
    }

    m_width = newWidth;
    m_height = newHeight;

    return true;
}

void FrameBuff::setFullViewport() const
{
    glViewport(0, 0, m_width, m_height);

}

void FrameBuff::copyColorToDefaultFrameBuffer() const
{
    const auto screenWidth = SetupWindow::getDefaultWindow()->getScreenWidth();
    const auto screenHeight = SetupWindow::getDefaultWindow()->getScreenHeight();

    bindAsRead();
    DefaultBuff::bindAsDraw();
    glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, screenWidth, screenHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void FrameBuff::copyDepthFromDefaultFrameBuffer() const
{
    // TODO: This function should work in theory, but copying depth results in strange
   // visual artifacts. I really don't know what am I doing wrong, I googled through entire internet
   // but to no avail. If anyone has an idea how to make this work properly, let me know really
    const auto screenWidth = SetupWindow::getDefaultWindow()->getScreenWidth();
    const auto screenHeight = SetupWindow::getDefaultWindow()->getScreenHeight();

    DefaultBuff::bindAsRead();
    bindAsDraw();

    glBlitFramebuffer(0, 0, screenWidth, screenHeight, 0, 0, m_width, m_height, GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
}

GLsizei FrameBuff::getWidth() const
{
    return m_width;
}

GLsizei FrameBuff::getHeight() const
{
    return m_height;
}

GLint FrameBuff::getDepthBits()
{
    if (m_depth != -1 || m_frameBufferID == 0) {
        return m_depth;
    }

    bindAsRead();
    glGetFramebufferAttachmentParameteriv(GL_READ_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE, &m_depth);
    const auto error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Could not read number of depth bits for framebuffer #" << m_frameBufferID << " (error " << error << ")! "
            << "Probably it has no depth attachment!" << std::endl;
    }

    return m_depth;
}

GLint FrameBuff::getStencilBits()
{
    if (m_stencil != -1 || m_frameBufferID == 0) {
        return m_stencil;
    }

    bindAsRead();
    glGetFramebufferAttachmentParameteriv(GL_READ_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, &m_stencil);
    const auto error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "Could not read number of stencil bits for framebuffer #" << m_frameBufferID << " (error " << error << ")! "
            << "Probably it has no stencil attachment!" << std::endl;
    }

    return m_stencil;
}

std::vector<GLubyte> FrameBuff::readColorValue(int x, int y)
{
    std::vector<GLubyte> result(4, 0);
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, result.data());
    return result;
}

void FrameBuff::deleteFrameBuffer()
{
    m_colorRenderBuffer.reset();
    m_depthRenderBuffer.reset();
    deleteOnlyFrameBuffer();
}

TextureLoader* FrameBuff::getTexture() const
{
    return m_texture.get();
}

bool FrameBuff::createAndBind(GLsizei width, GLsizei height)
{
    glGenFramebuffers(1, &m_frameBufferID);
    if (m_frameBufferID == 0)
    {
        std::cerr << "Unable to create framebuffer!" << std::endl;
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
    std::cout << "Created framebuffer with ID #" << m_frameBufferID << ", its dimensions will be [" << width << ", " << height << "]" << std::endl;
    m_width = width;
    m_height = height;

    return true;
}

bool FrameBuff::withColorAttachment(GLenum internalFormat)
{
    if (m_frameBufferID == 0) {
        return false;
    }

    // Create color render buffer and attach it to FBO
    auto colorRenderBuffer = std::make_unique<RenderBuff>();
    if (!colorRenderBuffer->create(internalFormat, m_width, m_height))
    {
        std::cerr << "Unable to create color attachment for the framebuffer #" << m_frameBufferID << "!" << std::endl;
        deleteFrameBuffer();
        return false;
    }

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderBuffer->getID());
    m_colorRenderBuffer = std::move(colorRenderBuffer);
    return true;
}

bool FrameBuff::withDepthAttachment(GLenum internalFormat)
{
    // Create depth buffer and attach it to FBO
    auto depthRenderBuffer = std::make_unique<RenderBuff>();
    if (!depthRenderBuffer->create(internalFormat, m_width, m_height))
    {
        std::cerr << "Unable to create depth attachment for the framebuffer #" << m_frameBufferID << "!" << std::endl;
        deleteFrameBuffer();
        return false;
    }

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer->getID());
   m_depthRenderBuffer = std::move(depthRenderBuffer);
    return true;
}

bool FrameBuff::withTextureColorAttachment(GLenum internalFormat)
{
    if (m_frameBufferID == 0) {
        return false;
    }

    // Create an empty texture with no data and same size as framebuffer has
    m_texture = std::make_unique<TextureLoader>();
    m_texture->createFromData(nullptr, m_width, m_height, internalFormat, false);
    m_texture->bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->getID(), 0);
    return true;
}

bool FrameBuff::finishInitialization() const
{
    if (m_frameBufferID == 0) {
        return false;
    }

    // Check FBO status when all attachments have been attached
    const auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (fboStatus != GL_FRAMEBUFFER_COMPLETE) {
        return false;
    }

    return true;
}

void FrameBuff::deleteOnlyFrameBuffer()
{
    if (m_frameBufferID == 0) {
        return;
    }

    std::cout << "Deleting framebuffer with ID #" << m_frameBufferID << std::endl;
    glDeleteFramebuffers(1, &m_frameBufferID);
    m_frameBufferID = 0;
    m_width = 0;
    m_height = 0;
    m_depth = -1;
    m_stencil = -1;
}
