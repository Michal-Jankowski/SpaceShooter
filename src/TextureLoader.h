#pragma once
#include "GLAD/glad.h"
#include <string>
class TextureLoader
{
public:
    ~TextureLoader();
    bool loadTexture2D(const std::string& filePath, bool shouldGenerateMipmaps = false);
	bool createFromData(const unsigned char* data, int width, int height, int bytesPerPixel, bool generateMipmaps = false);
    void bind(const int textureUnit = 0) const;
    void deleteTexture();
private:
    GLuint m_textureID = 0; 
    int m_width = 0; 
    int m_height = 0; 
    int m_bytesPerPixel = 0; 
    bool m_isLoaded = false; 
    std::string m_filePath; 
};

