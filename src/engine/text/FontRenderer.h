#pragma once
#pragma once

// STL
#include <map>
#include <memory>

// Project
#include "../utils/Buffer.h"
#include "../textures/TextureLoader.h"
#include "../textures/Sampler.h"
#include "../shaders/ShaderProgram.h"
#include "../utils/string_utils.h"




class FreeTypeFont
{
public:
    static const int CHARACTERS_TEXTURE_SIZE; // Size of texture atlas (in pixels) that stores characters
    static const std::string FREETYPE_FONT_PROGRAM_KEY; // Key for shader program for rendering fonts in 2D
    static const std::string FREETYPE_FONT_SAMPLER_KEY; // Key for sampler used for rendering fonts

    FreeTypeFont();
    ~FreeTypeFont();

    void addCharacterRange(unsigned int characterFrom, unsigned int characterTo);
    bool loadFont(const std::string& fontFilePath, int pixelSize);
    int getTextWidth(const std::string& text, int pixelSize = -1) const;
    int getTextHeight(int pixelSize = -1) const;
    void setTextColor(const glm::vec4& color);

    template <typename... Args>
    void print(int x, int y, const std::string& text, const Args&... args) const
    {
        printInternal(x, y, string_utils::formatString(text.c_str(), args...), -1);
    }

    template <typename... Args>
    void printWithCustomSize(int x, int y, int pixelSize, const std::string& text, const Args&... args) const
    {
        print(x, y, text, pixelSize, string_utils::formatString(text.c_str(), args...));
    }

    void deleteFont();

private:
    void printInternal(int x, int y, const std::string& text, int pixelSize) const;
    ShaderProgram& getFreetypeFontShaderProgram() const;
    const Sampler& getFreetypeFontSampler() const;
    struct CharacterProperties
    {
        int characterCode; 

        int width;
        int height;
        int advanceX;
        int bearingX;
        int bearingY;

        int renderIndex;
        int textureIndex;
    };

    
    struct CharacterRange
    {
        CharacterRange(unsigned int characterCodeFrom, unsigned int characterCodeTo)
        {
            m_characterCodeFrom = characterCodeFrom;
            m_characterCodeTo = characterCodeTo;
        }

        unsigned int m_characterCodeFrom; 
        unsigned int m_characterCodeTo; 
    };

    bool m_isLoaded = false; 
    std::vector<CharacterRange> m_characterRanges; 
    int m_pixelSize; 
    glm::vec4 m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    std::vector<std::unique_ptr<TextureLoader>> m_textures; 
    std::map<int, CharacterProperties> m_characterProperties;
    GLuint m_vao; 
    Buffer m_vbo; 
};