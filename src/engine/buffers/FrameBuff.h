#pragma once

#include <memory>
#include <vector>
#include "RenderBuff.h"
#include "../textures/TextureLoader.h"

class FrameBuff
{
public:
    ~FrameBuff();

    bool createFrameBufferWithColorAndDepthWithDefaultScreenSize();
    bool createFrameBufferWithColorAndDepth(GLsizei width, GLsizei height);

    void bindAsBothReadAndDraw() const;
    void bindAsRead() const;
    void bindAsDraw() const;

    bool resize(GLsizei newWidth, GLsizei newHeight);
    void setFullViewport() const;
    void copyColorToDefaultFrameBuffer() const;
    void copyDepthFromDefaultFrameBuffer() const;

    GLsizei getWidth() const;
    GLsizei getHeight() const;

    GLint getDepthBits();
    GLint getStencilBits();


    static std::vector<GLubyte> readColorValue(int x, int y);

    void deleteFrameBuffer();

    TextureLoader* getTexture() const;

private:
    friend class FrameBuffBuilder;

    bool createAndBind(GLsizei width, GLsizei height);
    bool withColorAttachment(GLenum internalFormat);
    bool withDepthAttachment(GLenum internalFormat);
    bool withTextureColorAttachment(GLenum internalFormat);
    bool finishInitialization() const;
    std::unique_ptr<RenderBuff> m_colorRenderBuffer;
    std::unique_ptr<RenderBuff> m_depthRenderBuffer;
    std::unique_ptr<TextureLoader> m_texture;

    GLuint m_frameBufferID = 0;
    GLsizei m_width = 0; 
    GLsizei m_height = 0; 
    GLint m_depth = -1; 
    GLint m_stencil = -1; 


    void deleteOnlyFrameBuffer();

};

