#include <glm/gtc/matrix_transform.hpp>

#include "HUD.h"
#include "../shaders/ShaderManager.h"
#include "../shaders/ShaderProgramManager.h"
#include "../textures/SamplerManager.h"

const std::string HUD::DEFAULT_FONT_KEY = "default";

HUD::HUD(const SetupWindow& window)
    : m_window(window)
{
    auto& sm = ShaderManager::getInstance();
    sm.loadVertexShader(ORTHO_2D_PROGRAM_KEY, "../src/shaders/ortho.vert");
    sm.loadFragmentShader(ORTHO_2D_PROGRAM_KEY, "../src/shaders/ortho.frag");
    auto& spm = ShaderProgramManager::getInstance();
    auto& shaderProgram = spm.createShaderProgram(ORTHO_2D_PROGRAM_KEY);
    shaderProgram.addShaderToProgram(sm.getVertexShader(ORTHO_2D_PROGRAM_KEY));
    shaderProgram.addShaderToProgram(sm.getFragmentShader(ORTHO_2D_PROGRAM_KEY));

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