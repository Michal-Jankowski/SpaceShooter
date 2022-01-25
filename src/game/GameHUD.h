#pragma once

#include "../engine/text/HUD.h"
#include "../engine/lighting/AmbientLight.h"

class GameHUD : public HUD
{
public:
    GameHUD(const SetupWindow& window);

    void renderHUD() const override {}
    void renderHUD(const AmbientLight& ambientLight);

    void addLines(const std::string& text, int lineCount = 1);


private:

    static constexpr int lineHeight = 30;
    static constexpr int lineOffsetX = 10;
    static constexpr int lineOffsetY = 140;

};