#include "TextureLoader.h"
#include <iostream>
#include <filesystem>
#define STB_IMAGE_IMPLEMENTATION
#include "../../../dependencies/stb/stb_image.h"

TextureLoader::~TextureLoader() {
    deleteTexture();
}

bool TextureLoader::loadTexture2D(const std::string& filePath, bool generateMipmaps)
{
    stbi_set_flip_vertically_on_load(1);
    int BPP;
    const auto data = stbi_load(filePath.c_str(), &m_width, &m_height, &BPP, 0);
    if (data == nullptr) {
        std::cerr << "ERROR: Failed to load image " << filePath << std::endl;
        return false;
    }

    GLenum format = 0;
    if (BPP == 4) {
        format = GL_RGBA;
    }
    else if (BPP == 3) {
        format = GL_RGB;
    }
    else if (BPP == 1) {
        format = GL_DEPTH_COMPONENT;
    }
    const auto result = createFromData(data, m_width, m_height, format, generateMipmaps);
    stbi_image_free(data);
    m_filePath = filePath;
    return result;
}
/// <summary>
///  Loads cubemap, mostly for cubemaps,
///  Can be used to generate objects refractions ("cube mapping")
///  Order: +X (right), -X (left), +Y (top), -Y (bottom), +Z (front), -Z (back)
/// </summary>
/// <param name="directorPath"></param>
/// <returns></returns>
bool TextureLoader::loadCubemap(const std::string directorPath) {

    constexpr auto skyboxSize = 6;
    std::vector<std::string> skyboxFaces;
    for (const auto& entry : std::filesystem::directory_iterator(directorPath)) {
        std::string  path_string{ entry.path().string() };
        skyboxFaces.emplace_back(path_string);
    }
    if (skyboxFaces.size() != skyboxSize) {
        std::cerr << "ERROR: Cubemap is of inccorrect size " << skyboxFaces.size() << std::endl;
        return false;
    }
    auto index = [&skyboxFaces](auto const& it) {
        return std::distance(std::begin(skyboxFaces), it);
    };
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
    stbi_set_flip_vertically_on_load(0);
    int imgWidth, imgHeight, BPP;
    for (auto face = std::begin(skyboxFaces); face != std::end(skyboxFaces); ++face) {
        const auto data = stbi_load((*face).c_str(), &imgWidth, &imgHeight, &BPP, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index(face), 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cerr << "ERROR: Failed to load texture from cubemap faces " << *face << std::endl;
            return false;
        }
        
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    m_isLoaded = true;
    return true; 
   
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

void TextureLoader::bind(const int textureNumber) const {
    if (!m_isLoaded) {
        return;
    }
    glActiveTexture(GL_TEXTURE0 + textureNumber);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void TextureLoader::bindCubemap(const int textureNumber) const {
    if (!m_isLoaded) {
        return;
    }
    glActiveTexture(GL_TEXTURE0 + textureNumber);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
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
    const auto format = m_format;
    deleteTexture();
    return createFromData(nullptr, m_width, m_height, format, false);
}

void TextureLoader::deleteTexture() {

    if (!m_isLoaded) {
        return;
    }
    glDeleteTextures(1, &m_textureID);
    m_textureID = 0;
    m_isLoaded = false;
}