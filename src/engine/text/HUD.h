#pragma once

#include <string>
#include <glm/glm.hpp>
#include "../core/SetupWindow.h"
#include "FontManager.h"

class HUD
{
public:
    HUD(const SetupWindow& window);
    virtual void renderHUD() const = 0;

protected:
    const SetupWindow& m_window;
    static const std::string DEFAULT_FONT_KEY;
    const std::string ORTHO_2D_PROGRAM_KEY = "ortho_2D";
    const std::string HUD_SAMPLER_KEY = "HUD";
   
    int getWidth() const;
    int getHeight() const;


    class PrintBuilder
    {
    public:
        PrintBuilder(const HUD& hud) : m_hud(hud) {};

        PrintBuilder& withFont(const std::string& fontKey) {
            m_fontKey = fontKey;
            return *this;
        }

        PrintBuilder& fromLeft() {
            m_fromRight = false;
            return *this;
        }

        PrintBuilder& fromRight() {
            m_fromRight = true;
            return *this;
        }

        PrintBuilder& fromTop() {
            m_fromTop = true;
            return *this;
        }

        PrintBuilder& fromBottom() {
            m_fromTop = false;
            return *this;
        }

        PrintBuilder& withPixelSize(int pixelSize) {
            m_pixelSize = pixelSize;
            return *this;
        }

        PrintBuilder& withColor(const glm::vec4& color) {
            m_color = color;
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
            auto& font = FreeTypeFontManager::getInstance().getFreeTypeFont(m_fontKey);
            const auto textWidth = font.getTextWidth(text, m_pixelSize);
            const auto textHeight = font.getTextHeight(m_pixelSize);
            if (m_fromRight) {
                x = m_hud.getWidth() - x - textWidth;
            }
            if (m_fromTop) {
                y = m_hud.getHeight() - y - textHeight;
            }

            font.setTextColor(m_color);
            font.print(x, y, text);
        }

        const HUD& m_hud;
        bool m_fromRight = false;
        bool m_fromTop = true;
        int m_pixelSize = -1;
        glm::vec4 m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        std::string m_fontKey = DEFAULT_FONT_KEY;
    };

    PrintBuilder printBuilder() const {
        return PrintBuilder(*this);
    }
};