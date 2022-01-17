// STL
#include <mutex>

// Project
#include "GameHUD.h"

std::ostream& operator<<(std::ostream& o, const glm::vec3& vec3)
{
    return o << std::setprecision(3) << "[" << vec3.x << ", " << vec3.y << ", " << vec3.z << "]";
}


GameHUD::GameHUD(const SetupWindow& window)
    : HUD(window)
{
    static std::once_flag prepareOnceFlag;
    std::call_once(prepareOnceFlag, []()
        {
            FreeTypeFontManager::getInstance().loadSystemFreeTypeFont(DEFAULT_FONT_KEY, "arial.ttf", 24);
        });
}

void GameHUD::renderHUD(const AmbientLight& ambientLight) const
{
    printBuilder().print(10, 10, "FPS: {}", _window.getFPS());
    printBuilder().print(10, 40, "Vertical Synchronization: {} (Press F3 to toggle)", _window.isVerticalSynchronizationEnabled() ? "On" : "Off");

    // Print information about ambient light
    printBuilder().print(10, 70, "Ambient light: {} (Press 'Z' to toggle)", ambientLight.m_isOn ? "On" : "Off");
    printBuilder().print(10, 100, " - color: {} (Press '1' and '2' to change)", ambientLight.m_color);

    // Print information about point light properties
    printBuilder()
        .fromRight()
        .fromBottom()
        .print(10, 10, "SpaceShooter");
}

void GameHUD::addLines(const std::string &text, int lineCount) {
    printBuilder().print(lineOffsetX, lineOffsetY + lineHeight * currentLines, text);
    currentLines += lineCount;
}

void GameHUD::clearLines() {
    currentLines = 0;
}


