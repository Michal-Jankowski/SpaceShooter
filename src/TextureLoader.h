#pragma once
#include "GLAD/glad.h"
#include <string>
class TextureLoader
{
public:
    bool loadTexture2D(const std::string& filePath, bool shouldGenerateMipmaps);
	bool createFromData(const unsigned char* data, int width, int height, int bytesPerPixel, bool generateMipmaps = false);
private:
    GLuint textureID_ = 0; 
    int m_width = 0; 
    int m_height = 0; 
    int m_bytesPerPixel = 0; 
    bool m_isLoaded = false; 
    std::string m_filePath; 
};

