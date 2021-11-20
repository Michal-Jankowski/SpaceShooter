#pragma once
#include <GLAD/glad.h>

class RenderBuff
{
public:
	~RenderBuff();

	bool create(GLenum format, GLsizei width, GLsizei height);
	bool resize(GLsizei width, GLsizei height);
    GLuint getID() const;
    void deleteRenderBuff();

private:

    GLuint m_renderBufferID = 0; 
    GLenum m_format = 0; 
    GLsizei m_width = 0; 
    GLsizei m_height = 0; 
    GLint m_depth = -1; 
    GLint m_stencil = -1; 
};

