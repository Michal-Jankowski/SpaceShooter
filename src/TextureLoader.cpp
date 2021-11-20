#include "TextureLoader.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../dependencies/stb/stb_image.h"

TextureLoader::~TextureLoader() {
    deleteTexture();
}

bool TextureLoader::loadTexture2D(const std::string& filePath, bool generateMipmaps)
{
    stbi_set_flip_vertically_on_load(1);
    int bytesPerPixel;
    const auto imageData = stbi_load(filePath.c_str(), &m_width, &m_height, &bytesPerPixel, 0);
    if (imageData == nullptr)
    {
        std::cout << "Failed to load image " << filePath << "!" << std::endl;
        return false;
    }

    GLenum format = 0;
    if (bytesPerPixel == 4) {
        format = GL_RGBA;
    }
    else if (bytesPerPixel == 3) {
        format = GL_RGB;
    }
    else if (bytesPerPixel == 1) {
        format = GL_DEPTH_COMPONENT;
    }
    const auto result = createFromData(imageData, m_width, m_height, format, generateMipmaps);
    stbi_image_free(imageData);
    m_filePath = filePath;
    return result;
}

bool TextureLoader::createFromData(const unsigned char* data, GLsizei width, GLsizei height, GLenum format, bool generateMipmaps) {
    if (m_isLoaded) {
        std::cerr << "Accessing non loaded texture!" << std::endl;
        return false;
    }

    m_width = width;
    m_height = height;
    m_format = format;

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);

    if (generateMipmaps) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    m_isLoaded = true;
    return true;
}

void TextureLoader::bind(const int textureUnit) const {
    if (!m_isLoaded) {
        std::cerr << "Accessing non loaded texture!" << std::endl;
        return;
    }
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

GLuint TextureLoader::getID() const
{
    return m_textureID;
}

GLenum TextureLoader::getFormat() const {
    return m_format;
}

bool TextureLoader::resize(GLsizei width, GLsizei height)
{
    if (!m_isLoaded) {
        return false;
    }

    const auto oldFormat = m_format;
    deleteTexture();

    return createFromData(nullptr, m_width, m_height, oldFormat, false);
}

void TextureLoader::deleteTexture() {

    if (!m_isLoaded) {
        return;
    }
    glDeleteTextures(1, &m_textureID);
    m_textureID = 0;
    m_isLoaded = false;
}