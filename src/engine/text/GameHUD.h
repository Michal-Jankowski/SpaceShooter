#pragma once

#include "HUD.h"
#include "../lighting/AmbientLight.h"

class GameHUD : public HUD
{
public:
    GameHUD(const SetupWindow& window);

    void renderHUD() const override {}
    void renderHUD(const AmbientLight& ambientLight);

    void addLines(const std::string& text, int lineCount = 1);
    void clearLines();

private:
    int m_currentLines = 0;
};