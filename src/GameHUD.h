#pragma once

// Project
#include "SetupWindow.h"
#include "HUD.h"
#include "AmbientLight.h"

class GameHUD : public HUD
{
public:
    GameHUD(const SetupWindow& window);

    void renderHUD() const override {} // Don't need this, but had to override, so that class is not abstract
    void renderHUD(const AmbientLight& ambientLight) const;
};