// STL
#include <algorithm>
#include <mutex>
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>
#include <GLAD/glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "FontRenderer.h"
#include "../shaders/ShaderManager.h"
#include "../shaders/ShaderProgramManager.h"
#include "../textures/SamplerManager.h"
#include "../maths/MatrixManager.h"
#include "../textures/TextureManager.h"

using namespace std;

const int FreeTypeFont::CHARACTERS_TEXTURE_SIZE = 256;
const std::string FreeTypeFont::FONT_PROGRAM_KEY = "freetype_font";
const std::string FreeTypeFont::FONT_SAMPLER_KEY = "freetype_font";

FreeTypeFont::FreeTypeFont()
{
    static std::once_flag prepareOnceFlag;
    std::call_once(prepareOnceFlag, []()
        {
            auto& sm = ShaderManager::getInstance();
            sm.loadVertexShader(FONT_PROGRAM_KEY, "../src/shaders/ortho.vert");
            sm.loadFragmentShader(FONT_PROGRAM_KEY, "../src/shaders/ortho.frag");

            auto& spm = ShaderProgramManager::getInstance();
            auto& shaderProgram = spm.createShaderProgram(FONT_PROGRAM_KEY);
            shaderProgram.addShaderToProgram(sm.getVertexShader(FONT_PROGRAM_KEY));
            shaderProgram.addShaderToProgram(sm.getFragmentShader(FONT_PROGRAM_KEY));
            shaderProgram.linkProgram();

            auto& smm = SamplerManager::getInstance();
            auto& sampler = smm.createSampler(FONT_SAMPLER_KEY, FilterOptions::MAG_FILTER_BILINEAR, FilterOptions::MIN_FILTER_NEAREST);
            sampler.setRepeat(false);
        });

    addCharacterRange(32, 127);
}

FreeTypeFont::~FreeTypeFont()
{
    deleteFont();
}

void FreeTypeFont::addCharacterRange(unsigned int characterFrom, unsigned int characterTo)
{
    m_characterRanges.push_back(CharacterRange(characterFrom, characterTo));
}

bool FreeTypeFont::loadFont(const std::string& fontFilePath, int pixelSize)
{
    if (pixelSize < 1 || pixelSize > CHARACTERS_TEXTURE_SIZE)
    {
        throw std::runtime_error("Cannot load font, because of invalid texture size");
    }

    FT_Library freeTypeLibrary;
    FT_Face freeTypeFace;

    auto ftError = FT_Init_FreeType(&freeTypeLibrary);
    if (ftError) {
        return false;
    }

    ftError = FT_New_Face(freeTypeLibrary, fontFilePath.c_str(), 0, &freeTypeFace);
    if (ftError) {
        return false;
    }

    FT_Set_Pixel_Sizes(freeTypeFace, 0, pixelSize);
    m_pixelSize = pixelSize;

    std::vector<unsigned char> textureData(CHARACTERS_TEXTURE_SIZE * CHARACTERS_TEXTURE_SIZE, 0);
    long long currentPixelPositionRow = 0;
    auto currentPixelPositionCol = 0;
    long long rowHeight = 0;
    auto currentRenderIndex = 0;
    std::unique_ptr<TextureLoader> texture = std::make_unique<TextureLoader>();

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    m_vbo.create();
    m_vbo.bind();

    auto finalizeTexture = [this, &texture, &textureData](bool createNext)
    {
        texture->createFromData(textureData.data(), CHARACTERS_TEXTURE_SIZE, CHARACTERS_TEXTURE_SIZE, GL_DEPTH_COMPONENT, true);
        m_textures.push_back(std::move(texture));
        if (createNext)
        {
            texture = std::make_unique<TextureLoader>();
            memset(textureData.data(), 0, textureData.size());
        }
    };

    for (const auto& characterRange : m_characterRanges)
    {
        for (auto c = characterRange.m_characterCodeFrom; c <= characterRange.m_characterCodeTo;)
        {
            FT_Load_Glyph(freeTypeFace, FT_Get_Char_Index(freeTypeFace, c), FT_LOAD_DEFAULT);
            FT_Render_Glyph(freeTypeFace->glyph, FT_RENDER_MODE_NORMAL);

            const auto* ptrBitmap = &freeTypeFace->glyph->bitmap;
            const int bmpWidth = ptrBitmap->width;
            const int bmpHeight = ptrBitmap->rows;
            const auto rowsLeft = CHARACTERS_TEXTURE_SIZE - currentPixelPositionRow;
            const auto colsLeft = CHARACTERS_TEXTURE_SIZE - currentPixelPositionCol;

            rowHeight = std::max(rowHeight, static_cast<long long>(bmpHeight));

            if (colsLeft < bmpWidth)
            {
                currentPixelPositionCol = 0;
                currentPixelPositionRow += rowHeight + 1;
                rowHeight = 0;
                continue;
            }

            if (rowsLeft < bmpHeight)
            {
                finalizeTexture(true);
                currentPixelPositionCol = 0;
                currentPixelPositionRow = 0;
                rowHeight = 0;
                continue;
            }

            auto& charProps = m_characterProperties[c];
            charProps.characterCode = c;
            charProps.width = freeTypeFace->glyph->metrics.width >> 6;
            charProps.bearingX = freeTypeFace->glyph->metrics.horiBearingX >> 6;
            charProps.advanceX = freeTypeFace->glyph->metrics.horiAdvance >> 6;
            charProps.height = freeTypeFace->glyph->metrics.height >> 6;
            charProps.bearingY = freeTypeFace->glyph->metrics.horiBearingY >> 6;

            if (bmpWidth == 0 && bmpHeight == 0) {
                charProps.renderIndex = -1;
                charProps.textureIndex = -1;
                c++;
                continue;
            }

            for (auto i = 0; i < bmpHeight; i++)
            {
                long long globalRow = currentPixelPositionRow + i;
                long long reversedRow = bmpHeight - i - 1;
                memcpy(textureData.data() + globalRow * CHARACTERS_TEXTURE_SIZE + currentPixelPositionCol, ptrBitmap->buffer + reversedRow * bmpWidth, bmpWidth);
            }

            glm::vec2 vertices[] =
                    {
                            glm::vec2(static_cast<float>(charProps.bearingX), static_cast<float>(charProps.bearingY)),
                            glm::vec2(static_cast<float>(charProps.bearingX), static_cast<float>(charProps.bearingY - charProps.height)),
                            glm::vec2(static_cast<float>(bmpWidth + charProps.bearingX), static_cast<float>(charProps.bearingY)),
                            glm::vec2(static_cast<float>(bmpWidth + charProps.bearingX), static_cast<float>(charProps.bearingY - charProps.height))
                    };

            glm::vec2 textureCoordinates[] =
                    {
                            glm::vec2(static_cast<float>(currentPixelPositionCol) / static_cast<float>(CHARACTERS_TEXTURE_SIZE), static_cast<float>(currentPixelPositionRow + bmpHeight) / static_cast<float>(CHARACTERS_TEXTURE_SIZE)),
                            glm::vec2(static_cast<float>(currentPixelPositionCol) / static_cast<float>(CHARACTERS_TEXTURE_SIZE), static_cast<float>(currentPixelPositionRow) / static_cast<float>(CHARACTERS_TEXTURE_SIZE)),
                            glm::vec2(static_cast<float>(currentPixelPositionCol + bmpWidth) / static_cast<float>(CHARACTERS_TEXTURE_SIZE), static_cast<float>(currentPixelPositionRow + bmpHeight) / static_cast<float>(CHARACTERS_TEXTURE_SIZE)),
                            glm::vec2(static_cast<float>(currentPixelPositionCol + bmpWidth) / static_cast<float>(CHARACTERS_TEXTURE_SIZE), static_cast<float>(currentPixelPositionRow) / static_cast<float>(CHARACTERS_TEXTURE_SIZE))
                    };

            for (int i = 0; i < 4; i++)
            {
                m_vbo.addData(&vertices[i], sizeof(vertices[i]));
                m_vbo.addData(&textureCoordinates[i], sizeof(textureCoordinates[i]));
            }

            charProps.renderIndex = currentRenderIndex;
            charProps.textureIndex = static_cast<int>(m_textures.size());
            currentPixelPositionCol += bmpWidth + 1;
            currentRenderIndex += 4;
            c++;
        }
    }

    if (currentPixelPositionRow > 0 || currentPixelPositionCol > 0) {
        finalizeTexture(false);
    }

    m_vbo.upload(GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2) * 2, reinterpret_cast<void*>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2) * 2, reinterpret_cast<void*>(sizeof(glm::vec2)));

    FT_Done_Face(freeTypeFace);
    FT_Done_FreeType(freeTypeLibrary);

    m_isLoaded = true;
    return true;
}

void FreeTypeFont::printInternal(int x, int y, const std::string& text, int pixelSize) const
{
    if (!m_isLoaded) {
        return;
    }

    glDisable(GL_DEPTH_TEST);
    glDepthMask(0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    auto& shaderProgram = getFreetypeFontShaderProgram();
    shaderProgram.useProgram();
    shaderProgram.setUniform("matrices.projectionMatrix", MatrixManager::getInstance().getOrthoProjectionMatrix());
    shaderProgram.setUniform("color", m_color);

    getFreetypeFontSampler().bind();
    shaderProgram.setUniform("sampler", 0);

    glm::vec2 currentPos(x, y);
    const auto usedPixelSize = pixelSize == -1 ? m_pixelSize : pixelSize;
    auto lastBoundTextureIndex = -1;
    const auto scale = static_cast<float>(usedPixelSize) / static_cast<float>(m_pixelSize);

    glBindVertexArray(m_vao);
    for (const auto& c : text)
    {
        if (c == '\n' || c == '\r')
        {
            currentPos.x = static_cast<float>(x);
            currentPos.y -= static_cast<float>(usedPixelSize);
            continue;
        }

        if (m_characterProperties.count(c) == 0) {
            continue;
        }

        const auto& props = m_characterProperties.at(c);
        if (props.renderIndex != -1)
        {
            if (lastBoundTextureIndex != props.textureIndex)
            {
                lastBoundTextureIndex = props.textureIndex;
                m_textures.at(props.textureIndex)->bind();
            }

            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(currentPos.x, currentPos.y, 0.0f));
            model = glm::scale(model, glm::vec3(scale, scale, 1.0f));
            shaderProgram.setUniform("matrices.modelMatrix", model);
            glDrawArrays(GL_TRIANGLE_STRIP, props.renderIndex, 4);
        }

        currentPos.x += props.advanceX * scale;
    }

    glDisable(GL_BLEND);
    glDepthMask(1);
    glEnable(GL_DEPTH_TEST);
}

int FreeTypeFont::getTextWidth(const std::string& text, int pixelSize) const
{
    float result = 0.0f;
    float rowWidth = 0.0f;
    const auto usedPixelSize = pixelSize == -1 ? m_pixelSize : pixelSize;
    const auto scale = static_cast<float>(usedPixelSize) / static_cast<float>(m_pixelSize);

    for (auto i = 0; i < static_cast<int>(text.length()); i++)
    {
        if (text[i] == '\n' || text[i] == '\r') {
            continue;
        }

        bool lastCharacterInRow = i == text.length() - 1 || text[i + 1] == '\n' || text[i + 1] == '\r';
        const auto& props = m_characterProperties.at(text[i]);
        if (!lastCharacterInRow)
        {
            rowWidth += props.advanceX * scale;
            continue;
        }

        rowWidth += (props.bearingX + props.width) * scale;
        result = std::max(result, rowWidth);
        rowWidth = 0.0f;
    }

    return static_cast<int>(ceil(result));
}

int FreeTypeFont::getTextHeight(int pixelSize) const
{
    const auto usedPixelSize = pixelSize == -1 ? m_pixelSize : pixelSize;
    const auto scale = static_cast<float>(usedPixelSize) / static_cast<float>(m_pixelSize);

    return static_cast<int>(ceil(usedPixelSize * scale));
}

void FreeTypeFont::setTextColor(const glm::vec4& color)
{
    m_color = color;
}

ShaderProgram& FreeTypeFont::getFreetypeFontShaderProgram() const
{
    return ShaderProgramManager::getInstance().getShaderProgram(FONT_PROGRAM_KEY);
}

const Sampler& FreeTypeFont::getFreetypeFontSampler() const
{
    return SamplerManager::getInstance().getSampler(FONT_SAMPLER_KEY);
}

void FreeTypeFont::deleteFont()
{
    if (!m_isLoaded) {
        return;
    }

    m_textures.clear();
    m_characterProperties.clear();
    m_characterRanges.clear();

    m_vbo.deleteBuffer();
    glDeleteVertexArrays(1, &m_vao);

   m_isLoaded = false;
}


