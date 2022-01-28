#include "GameHUD.h"

GameHUD::GameHUD(const SetupWindow& window)
    : HUD(window, "./res/fonts/TurretRoad-Bold.ttf", 22) {
}

void GameHUD::renderHUD()
{
    m_fromRight = false;
    m_fromTop = true;
    print(10, 10, "FPS: {}", m_window.getFPS());
    print(10, 40, "VSync: {} (Press 0 to toggle)", m_window.isVerticalSynchronizationEnabled() ? "On" : "Off");

    m_fromRight = true;
    m_fromTop = false;

    print(10, 10, "SpaceShooter");
}

void GameHUD::addLines(const std::string &text, int lineCount) {
    HUD::addLines(text, lineCount,lineOffsetX,lineOffsetY, lineHeight);
}




