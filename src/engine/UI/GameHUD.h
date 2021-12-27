#pragma once

// Project


#include "../text/HUD.h"

class GameHUD : public HUD
{
public:
    GameHUD(const SetupWindow& window);

    void renderHUD() const override {} // Don't need this, but had to override, so that class is not abstract
    //void renderHUD(const AmbientLight& ambientLight) const;

    template <typename... Args>
    void addLines(const std::string& text, int lineCount = 1, const Args&... args);
    void clearLines();

private:
    const int lineHeight = 30;
    const int lineOffset = 10;
    int currentLines = 0;
};