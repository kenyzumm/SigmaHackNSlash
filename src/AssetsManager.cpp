#include "AssetsManager.h"


#include <iostream>

// Constructor: initializes logger
AssetsManager::AssetsManager() : m_log("AssetsManagerLogs.txt"){}
AssetsManager::~AssetsManager() {}

// Loads texture from file and saves it under the given name
void AssetsManager::loadTexture(std::string name, std::string filename) {
    sf::Texture texture;
    if (texture.loadFromFile(filename)) {
        this->m_textures[name] = texture; // Add texture to map
        LOG_DEBUG(m_log, "Texture \"" + name + "\" successfully loaded");
    } else {
        LOG_ERROR(m_log, "Texture \"" + name + "\" not loaded");
    }
}

// Loads font from file and saves it under the given name
void AssetsManager::loadFont(std::string name, std::string filename) {
    sf::Font font;
    if (font.openFromFile(filename)) {
        this->m_fonts[name] = font; // Add font to map
    } else {
        LOG_ERROR(m_log, "Font \"" + name + "\" not loaded");
    }
}

// Returns a reference to the texture with the given name (throws an exception if it does not exist)
sf::Texture &AssetsManager::getTexture(std::string name) {
    if (m_textures.find(name) == m_textures.end()) {
        LOG_ERROR(m_log, "Texture \"" + name + "\" not found");
        throw std::runtime_error("Texture not found: " + name);
    }
    return this->m_textures[name];
}

// Returns a reference to the font with the given name
sf::Font &AssetsManager::getFont(std::string name) {
    return this->m_fonts[name];
}
