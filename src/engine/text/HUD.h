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


    HUD& fromLeft() {
        m_fromRight = false;
        return *this;
    }

    HUD& fromRight() {
        m_fromRight = true;
        return *this;
    }

    HUD& fromTop() {
        m_fromTop = true;
        return *this;
    }

    HUD& fromBottom() {
        m_fromTop = false;
        return *this;
    }

    HUD& withPixelSize(int pixelSize) {
        m_pixelSize = pixelSize;
        return *this;
    }

    HUD& withColor(const glm::vec4& color) {
        m_color = color;
        return *this;
    }

    template <typename... Args>
    void print(int x, int y, const std::string& text, const Args&... args) const{
        printInternal(x, y, string_utils::formatString(text, args...));
    }

protected:
    const SetupWindow& m_window;
    std::unique_ptr<FreeTypeFont> font;
    const std::string ORTHO_2D_PROGRAM_KEY = "ortho_2D";
    const std::string HUD_SAMPLER_KEY = "HUD";

    int getWidth() const;
    int getHeight() const;

private:
    void printInternal(int x, int y, const std::string& text) const;
    bool m_fromRight = false;
    bool m_fromTop = true;
    int m_pixelSize = -1;
    glm::vec4 m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

};