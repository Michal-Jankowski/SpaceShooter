#pragma once

// Project


#include "HUD.h"
#include "../lighting/AmbientLight.h"

class GameHUD : public HUD
{
public:
    GameHUD(const SetupWindow& window);

    void renderHUD() const override {} // Don't need this, but had to override, so that class is not abstract
    void renderHUD(const AmbientLight& ambientLight) const;

    void addLines(const std::string& text, int lineCount = 1);
    void clearLines();

private:
    const int lineHeight = 30;
    const int lineOffsetX = 10;
    const int lineOffsetY = 140;
    int currentLines = 0;
};