#pragma once

// Project


#include "../../engine/text/HUD.h"

class GameHUD : public HUD
{
public:
    GameHUD(const SetupWindow& window);

    void renderHUD() const override {} // Don't need this, but had to override, so that class is not abstract
    void renderHUD(const AmbientLight& ambientLight) const;
};