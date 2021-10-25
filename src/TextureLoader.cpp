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
    const auto imageData = stbi_load(filePath.c_str(), &m_width, &m_height, &m_bytesPerPixel, 0);
    if (imageData == nullptr)
    {
        std::cout << "Failed to load image " << filePath << "!" << std::endl;
        return false;
    }

    const auto result = createFromData(imageData, m_width, m_height, m_bytesPerPixel, generateMipmaps);
    stbi_image_free(imageData);
    m_filePath = filePath;
    return result;
}

bool TextureLoader::createFromData(const unsigned char* data, int width, int height, int bytesPerPixel, bool generateMipmaps) {
    if (m_isLoaded) {
        std::cerr << "Accessing non loaded texture!" << std::endl;
        return false;
    }

    m_width = width;
    m_height = height;
    m_bytesPerPixel = bytesPerPixel;

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    GLenum internalFormat = 0;
    GLenum format = 0;
    if (m_bytesPerPixel == 4) {
        internalFormat = format = GL_RGBA;
    }
    else if (m_bytesPerPixel == 3) {
        internalFormat = format = GL_RGB;
    }
    else if (m_bytesPerPixel == 1) {
        internalFormat = format = GL_DEPTH_COMPONENT;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);

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

void TextureLoader::deleteTexture() {

    if (!m_isLoaded) {
        return;
    }
    glDeleteTextures(1, &m_textureID);
    m_textureID = 0;
    m_isLoaded = false;
}