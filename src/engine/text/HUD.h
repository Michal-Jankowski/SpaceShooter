#pragma once

#include <string>
#include <glm/glm.hpp>
#include "../core/SetupWindow.h"
#include "FontRenderer.h"

class HUD
{
public:
    HUD(const SetupWindow& window, const std::string & fontPath, int fontSize);
    virtual void renderHUD() const = 0;

    template <typename... Args>
    void print(int x, int y, const std::string& text, const Args&... args) const{
        printInternal(x, y, string_utils::formatString(text, args...));
    }
    void addLines(const std::string &text, int lineCount, int lineOffsetX, int lineOffsetY, int lineHeight);
    void clearLines();
protected:
    const SetupWindow& m_window;
    std::unique_ptr<FreeTypeFont> font;
    const std::string ORTHO_2D_PROGRAM_KEY = "ortho_2D";
    const std::string HUD_SAMPLER_KEY = "HUD";

    int getWidth() const;
    int getHeight() const;

    bool m_fromRight = false;
    bool m_fromTop = true;

private:
    void printInternal(int x, int y, const std::string& text) const;

    int m_pixelSize = -1;
    glm::vec4 m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    int m_currentLines = 0;

    static constexpr int lineHeight = 30;
    static constexpr int lineOffsetX = 10;
    static constexpr int lineOffsetY = 140;

};