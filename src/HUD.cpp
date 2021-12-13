#pragma once

// STL
#include <string>

// GLM
#include <glm/glm.hpp>

// Project
#include "stringUtils.h"
#include "OpenGLWindow.h"
#include "static_meshes_2D/primitives/quad.h"
#include "shaderProgram.h"
#include "sampler.h"
#include "freeTypeFontManager.h"

/**
 * Base class for rendering HUD (head-up display) over scene.
 */
class HUD
{
public:
    static const std::string DEFAULT_FONT_KEY;
    static const std::string ORTHO_2D_PROGRAM_KEY; // Key for shader program for rendering in 2D
    static const std::string HUD_SAMPLER_KEY; // Key for sampler used for HUD objects

    HUD(const OpenGLWindow& window);

    /**
     * Renders HUD.
     */
    virtual void renderHUD() const = 0;

protected:
    const OpenGLWindow& _window; // OpenGL Window class instance, for which HUD is rendered

    /**
     * Gets HUD width.
     */
    int getWidth() const;

    /**
     * Gets HUD height.
     */
    int getHeight() const;

    /**
     * Renders 2D textured quad at specified position with specified size. Possibility to render from right or top as well.
     *
     * @param x               Rendering position from left or from right edge (depending on fromRight flag)
     * @param y               Rendering position from top or bottom edge (depending on fromTop flag)
     * @param renderedWidth   Width of rendered quad (in pixels)
     * @param renderedHeight  Height of rendered quad (in pixels)
     * @param fromRight       Flag telling, if you want to render from right side instead of from left side
     * @param fromTop         Flag telling, if you want to render from top side instead of from bottom side
     */
    void renderTexturedQuad2D(int x, int y, int renderedWidth, int renderedHeight, bool fromRight = false, bool fromTop = false) const;

    class PrintBuilder
    {
    public:
        PrintBuilder(const HUD& hud) : _hud(hud) {};

        PrintBuilder& withFont(const std::string& fontKey) {
            _fontKey = fontKey;
            return *this;
        }

        PrintBuilder& fromLeft() {
            _fromRight = false;
            return *this;
        }

        PrintBuilder& fromRight() {
            _fromRight = true;
            return *this;
        }

        PrintBuilder& fromTop() {
            _fromTop = true;
            return *this;
        }

        PrintBuilder& fromBottom() {
            _fromTop = false;
            return *this;
        }

        PrintBuilder& withPixelSize(int pixelSize) {
            _pixelSize = pixelSize;
            return *this;
        }

        PrintBuilder& withColor(const glm::vec4& color) {
            _color = color;
            return *this;
        }

        /**
         * Prints text at given position with all parameters.
         */
        template <typename... Args>
        void print(int x, int y, const std::string& text, const Args&... args) const
        {
            printInternal(x, y, string_utils::formatString(text, args...));
        }

    private:
        void printInternal(int x, int y, const std::string& text) const
        {
            auto& font = FreeTypeFontManager::getInstance().getFreeTypeFont(_fontKey);
            const auto textWidth = font.getTextWidth(text, _pixelSize);
            const auto textHeight = font.getTextHeight(_pixelSize);
            if (_fromRight) {
                x = _hud.getWidth() - x - textWidth;
            }
            if (_fromTop) {
                y = _hud.getHeight() - y - textHeight;
            }

            font.setTextColor(_color);
            font.print(x, y, text);
        }
        // STL
#include <mutex>

// GLM
#include <glm/gtc/matrix_transform.hpp>

// Project
#include "HUD.h"

#include "shaderManager.h"
#include "shaderProgramManager.h"
#include "samplerManager.h"

        const std::string HUD::DEFAULT_FONT_KEY = "default";
        const std::string HUD::ORTHO_2D_PROGRAM_KEY = "ortho_2D";
        const std::string HUD::HUD_SAMPLER_KEY = "HUD";

        HUD::HUD(const OpenGLWindow& window)
            : _window(window)
            , _texturedQuad(true, true)
        {
            static std::once_flag prepareOnceFlag;
            std::call_once(prepareOnceFlag, []()
                {
                    auto& sm = ShaderManager::getInstance();
                    sm.loadVertexShader(ORTHO_2D_PROGRAM_KEY, "data/shaders/tut009/ortho2D.vert");
                    sm.loadFragmentShader(ORTHO_2D_PROGRAM_KEY, "data/shaders/tut009/ortho2D.frag");

                    auto& spm = ShaderProgramManager::getInstance();
                    auto& shaderProgram = spm.createShaderProgram(ORTHO_2D_PROGRAM_KEY);
                    shaderProgram.addShaderToProgram(sm.getVertexShader(ORTHO_2D_PROGRAM_KEY));
                    shaderProgram.addShaderToProgram(sm.getFragmentShader(ORTHO_2D_PROGRAM_KEY));

                    auto& smm = SamplerManager::getInstance();
                    smm.createSampler(HUD_SAMPLER_KEY, MAG_FILTER_BILINEAR, MIN_FILTER_BILINEAR);
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

        void HUD::renderTexturedQuad2D(int x, int y, int renderedWidth, int renderedHeight, bool fromRight, bool fromTop) const
        {
            if (fromRight) {
                x = getWidth() - x - renderedWidth;
            }
            if (fromTop) {
                y = getHeight() - y - renderedHeight;
            }

            auto& shaderProgram = getOrtho2DShaderProgram();
            glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(static_cast<float>(x), static_cast<float>(y), 0.0f));
            model = glm::scale(model, glm::vec3(static_cast<float>(renderedWidth), static_cast<float>(renderedHeight), 1.0f));
            shaderProgram[ShaderConstants::modelMatrix()] = model;

            _texturedQuad.render();
        }

        ShaderProgram& HUD::getOrtho2DShaderProgram() const
        {
            return ShaderProgramManager::getInstance().getShaderProgram(ORTHO_2D_PROGRAM_KEY);
        }

        const Sampler& HUD::getHUDSampler() const
        {
            return SamplerManager::getInstance().getSampler(HUD_SAMPLER_KEY);
        }
        const HUD& _hud;
        bool _fromRight = false;
        bool _fromTop = true;
        int _pixelSize = -1;
        glm::vec4 _color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        std::string _fontKey = HUD::DEFAULT_FONT_KEY;
    };

    PrintBuilder printBuilder() const
    {
        return PrintBuilder(*this);
    }

    /**
     * Gets shader program for 2D rendering.
     */
    ShaderProgram& getOrtho2DShaderProgram() const;

    /**
     * Gets HUD sampler.
     */
    const Sampler& getHUDSampler() const;

    static_meshes_2D::Quad _texturedQuad; // Static mesh for rendering 2D quad
};