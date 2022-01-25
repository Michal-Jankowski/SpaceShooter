#include "GameHUD.h"

constexpr auto lineHeight = 30;
constexpr auto lineOffsetX = 10;
constexpr auto lineOffsetY = 140;

std::ostream& operator<<(std::ostream& o, const glm::vec3& vec3)
{
    return o << std::setprecision(3) << "[" << vec3.x << ", " << vec3.y << ", " << vec3.z << "]";
}


GameHUD::GameHUD(const SetupWindow& window)
    : HUD(window)
{
    FreeTypeFontManager::getInstance().loadSystemFreeTypeFont(DEFAULT_FONT_KEY, "arial.ttf", 24);
}

void GameHUD::renderHUD(const AmbientLight& ambientLight) const
{
    printBuilder().print(10, 10, "FPS: {}", m_window.getFPS());
    printBuilder().print(10, 40, "VSync: {} (Press 0 to toggle)", m_window.isVerticalSynchronizationEnabled() ? "On" : "Off");

    printBuilder()
        .fromRight()
        .fromBottom()
        .print(10, 10, "SpaceShooter");
}

void GameHUD::addLines(const std::string &text, int lineCount) {
    printBuilder().print(lineOffsetX, lineOffsetY + lineHeight * m_currentLines, text);
    m_currentLines += lineCount;
}

void GameHUD::clearLines() {
    m_currentLines = 0;
}


