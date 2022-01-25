#include <glm/gtc/matrix_transform.hpp>

#include "HUD.h"
#include "../shaders/ShaderManager.h"
#include "../shaders/ShaderProgramManager.h"
#include "../textures/SamplerManager.h"


HUD::HUD(const SetupWindow& window, const std::string & fontPath, int fontSize)
    : m_window(window)
{
    auto& sm = ShaderManager::getInstance();
    sm.loadVertexShader(ORTHO_2D_PROGRAM_KEY, "../src/shaders/ortho.vert");
    sm.loadFragmentShader(ORTHO_2D_PROGRAM_KEY, "../src/shaders/ortho.frag");
    auto& spm = ShaderProgramManager::getInstance();
    auto& shaderProgram = spm.createShaderProgram(ORTHO_2D_PROGRAM_KEY);
    shaderProgram.addShaderToProgram(sm.getVertexShader(ORTHO_2D_PROGRAM_KEY));
    shaderProgram.addShaderToProgram(sm.getFragmentShader(ORTHO_2D_PROGRAM_KEY));

    font = std::make_unique<FreeTypeFont>();
    if (!font->loadFont(fontPath, fontSize))
    {
        const auto msg = "Could not load FreeType font'" + fontPath + "'!";
        throw std::runtime_error(msg);
    }

    auto& smm = SamplerManager::getInstance();
    smm.createSampler(HUD_SAMPLER_KEY, FilterOptions::MAG_FILTER_BILINEAR, FilterOptions::MIN_FILTER_BILINEAR);
}

int HUD::getWidth() const
{
    int width, height;
    glfwGetFramebufferSize(m_window.getWindow(), &width, &height);
    return width;
}

int HUD::getHeight() const
{
    int width, height;
    glfwGetFramebufferSize(m_window.getWindow(), &width, &height);
    return height;
}

void HUD::printInternal(int x, int y, const std::string &text) const {

    {
        const auto textWidth = font->getTextWidth(text, m_pixelSize);
        const auto textHeight = font->getTextHeight(m_pixelSize);
        if (m_fromRight) {
            x = getWidth() - x - textWidth;
        }
        if (m_fromTop) {
            y = getHeight() - y - textHeight;
        }

        font->setTextColor(m_color);
        font->print(x, y, text);
    }

}


void HUD::addLines(const std::string &text, int lineCount, int lineOffsetX, int lineOffsetY, int lineHeight) {
    m_fromRight = false;
    m_fromTop = true;
    print(lineOffsetX, lineOffsetY + lineHeight * m_currentLines, text);
    m_currentLines += lineCount;
}

void HUD::clearLines() {
    m_currentLines = 0;
}
