#pragma once
#include "TextureLoader.h"
#include <map>
#include <memory>
class TextureManager
{
public:
	static TextureManager& getInstance();
	void loadTexture2D(const std::string& name, const std::string& fileName, bool generateMipmaps = true);
	void loadCubemap(const std::string& keyName, const std::string& path);
	bool deleteTexture(const std::string& name);
	const TextureLoader& getTexture(const std::string& key) const;
	bool hasTexture(const std::string& key) const;
	void clearTextureCache();

private:
	TextureManager() {}
	TextureManager(const TextureManager&) = delete;
	void operator=(const TextureManager&) = delete;

	std::map<std::string, std::unique_ptr<TextureLoader>> m_textureKeys;
};

