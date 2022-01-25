#pragma once

#include <string>
#include <map>
#include <memory>
#include "FontRenderer.h"

class FreeTypeFontManager
{
public:
    static FreeTypeFontManager& getInstance();
    FreeTypeFont& getFreeTypeFont(const std::string& key) const;
    void loadSystemFreeTypeFont(const std::string& key, const std::string& fontName, const int pixelSize);

private:
    FreeTypeFontManager() {}
    FreeTypeFontManager(const FreeTypeFontManager&) = delete;
    void operator=(const FreeTypeFontManager&) = delete;
    void loadFreeTypeFontFromFile(const std::string& key, const std::string& filePath, const int pixelSize);
    bool hasLoadedFont(const std::string& key) const;
    static const std::string& getOSFont();
    std::map<std::string, std::unique_ptr<FreeTypeFont>> m_fontHolder;
};