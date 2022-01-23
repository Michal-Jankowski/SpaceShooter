#include "TextureManager.h"
#include <stdexcept>
#include <vector>

TextureManager& TextureManager::getInstance() {
	static TextureManager textureManager;
	return textureManager;
}

void TextureManager::loadTexture2D(const std::string& name, const std::string& fileName, bool generateMipmaps) {
	if (containsTexture(name)) {
		return;
	}

	auto texturePtr = std::make_unique<TextureLoader>();
	if (!texturePtr->loadTexture2D(fileName, generateMipmaps)) {
		auto msg = "Could not load texture for key '" + name + "' from file '" + fileName;
		throw std::runtime_error(msg.c_str());
	}
	m_textureKeys[name] = std::move(texturePtr);
}

void TextureManager::loadCubemap(const std::string& keyName, const std::string& path) {
	auto texturePtr = std::make_unique<TextureLoader>();
	if (!texturePtr->loadCubemap(path)) {
		auto msg = "Could not load cubemap within path '" + path;
		throw std::runtime_error(msg.c_str());
	}
	m_textureKeys[keyName] = std::move(texturePtr);
}

bool TextureManager::deleteTexture(const std::string& name) {
	if (containsTexture(name)) {
		m_textureKeys.erase(name);
		return  true;
	}
	return false;
}

const TextureLoader& TextureManager::getTexture(const std::string& key) const {
	if (!containsTexture(key)) {
		auto msg = "Could not get texture for '" + key;
		throw std::runtime_error(msg.c_str());
	}
	return *m_textureKeys.at(key).get();
}

bool TextureManager::containsTexture(const std::string& key) const {
	return m_textureKeys.count(key) > 0;
}

void TextureManager::clearTextureCache() {
	m_textureKeys.clear();
}
