// STL
#include <mutex>

// GLM
#include <glm/gtc/matrix_transform.hpp>

// Project
#include "HUD.h"
#include "../shaders/ShaderManager.h"
#include "../shaders/ShaderProgramManager.h"
#include "../textures/SamplerManager.h"

const std::string HUD::DEFAULT_FONT_KEY = "default";
const std::string HUD::ORTHO_2D_PROGRAM_KEY = "ortho_2D";
const std::string HUD::HUD_SAMPLER_KEY = "HUD";

HUD::HUD(const SetupWindow& window)
    : _window(window)
{
    static std::once_flag prepareOnceFlag;
    std::call_once(prepareOnceFlag, []()
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
        });
}

int HUD::getWidth() const
{
    int width, height;
    glfwGetFramebufferSize(_window.getWindow(), &width, &height);
    return width;
}

int HUD::getHeight() const
{
    int width, height;
    glfwGetFramebufferSize(_window.getWindow(), &width, &height);
    return height;
}

ShaderProgram& HUD::getOrtho2DShaderProgram() const
{
    return ShaderProgramManager::getInstance().getShaderProgram(ORTHO_2D_PROGRAM_KEY);
}

const Sampler& HUD::getHUDSampler() const
{
    return SamplerManager::getInstance().getSampler(HUD_SAMPLER_KEY);
}