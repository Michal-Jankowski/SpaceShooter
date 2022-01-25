#include <mutex>
#include <windows.h>
#include "sysinfoapi.h"
#include "FontManager.h"

FreeTypeFontManager& FreeTypeFontManager::getInstance()
{
	static FreeTypeFontManager fm;
	return fm;
}


FreeTypeFont& FreeTypeFontManager::getFreeTypeFont(const std::string& key) const
{
	if (!hasLoadedFont(key))
	{
		const auto msg = "Attempting to get non-existing FreeType font with key '" + key + "'!";
		throw std::runtime_error(msg.c_str());
	}

	return *m_fontHolder.at(key);
}

void FreeTypeFontManager::loadFreeTypeFontFromFile(const std::string& key, const std::string& filePath, const int pixelSize) {

	if (hasLoadedFont(key))
	{
		const auto msg = "FreeType font with key '" + key + "' already exists!";
		throw std::runtime_error(msg.c_str());
	}

	auto freeTypeFont = std::make_unique<FreeTypeFont>();
	if (!freeTypeFont->loadFont(filePath, pixelSize))
	{
		const auto msg = "Could not load FreeType font'" + filePath + "'!";
		throw std::runtime_error(msg);
	}

	m_fontHolder[key] = std::move(freeTypeFont);
}

void FreeTypeFontManager::loadSystemFreeTypeFont(const std::string& key, const std::string& fontName, const int pixelSize)
{
	loadFreeTypeFontFromFile(key, getOSFont() + fontName, pixelSize);
}


bool FreeTypeFontManager::hasLoadedFont(const std::string& key) const
{
	return m_fontHolder.count(key) > 0;
}

const std::string& FreeTypeFontManager::getOSFont()
{
	static std::string systemFontsDirectory;
	static std::once_flag prepareOnceFlag;
	char buffer[512]; GetWindowsDirectory(buffer, 512);
	systemFontsDirectory = buffer;
	systemFontsDirectory += "\\Fonts\\";

	return systemFontsDirectory;
}