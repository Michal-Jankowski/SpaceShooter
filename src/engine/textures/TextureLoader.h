#pragma once
#include "GLAD/glad.h"
#include <string>
class TextureLoader
{
public:
    ~TextureLoader();
    bool loadTexture2D(const std::string& filePath, bool shouldGenerateMipmaps = false);
    bool loadCubemap(const std::string filesPath);
    bool createFromData(const unsigned char* data, GLsizei width, GLsizei height, GLenum format, bool generateMipmaps = false);
    void bind(const int textureNumber = 0) const;
    void bindCubemap(const int textureNumber = 0) const;
    GLuint getID() const;
    GLenum getFormat() const;
    bool resize(GLsizei width, GLsizei height);
    void deleteTexture();
private:
    GLuint m_textureID{ 0 };
    GLenum m_format{ 0 };
    GLsizei m_width{ 0 };
    GLsizei m_height{ 0 };
    bool m_isLoaded{ false };
    std::string m_filePath; 
};

