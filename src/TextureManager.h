#pragma once
#include "TextureLoader.h"
#include <map>
#include <memory>
class TextureManager
{
public:
	static TextureManager& getInstance();
	void loadTexture2D(const std::string& name, const std::string& fileName, bool generateMipmaps = true);
	bool deleteTexture(const std::string& name);
	const TextureLoader& getTexture(const std::string& key) const;
	bool containsTexture(const std::string& key) const;

private:
	TextureManager() {}
	TextureManager(const TextureManager&) = delete;
	void operator=(const TextureManager&) = delete;

	std::map<std::string, std::unique_ptr<TextureLoader>> m_textureKeys;
};

