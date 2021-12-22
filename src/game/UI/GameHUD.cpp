// STL
#include <mutex>

// Project
#include "GameHUD.h"
#include "../../engine/utils/ostreamUtils.h"

using namespace ostream_utils;


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