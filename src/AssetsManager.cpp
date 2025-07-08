#include "AssetsManager.h"


#include <iostream>

AssetsManager::AssetsManager() : m_log("AssetsManagerLogs.txt"){}
AssetsManager::~AssetsManager() {}
void AssetsManager::loadTexture(std::string name, std::string filename) {
    sf::Texture texture;
    if (texture.loadFromFile(filename)) {
        this->m_textures[name] = texture;
        LOG_DEBUG(m_log, "Texture \"" + name + "\" successfully loaded");
    } else {
        LOG_ERROR(m_log, "Texture \"" + name + "\" not loaded");
    }
}
void AssetsManager::loadFont(std::string name, std::string filename) {
    sf::Font font;
    if (font.openFromFile(filename)) {
        this->m_fonts[name] = font;
    } else {
        LOG_ERROR(m_log, "Font \"" + name + "\" not loaded");
    }
}

sf::Texture &AssetsManager::getTexture(std::string name) {
    if (m_textures.find(name) == m_textures.end()) {
        LOG_ERROR(m_log, "Texture \"" + name + "\" not found");
        throw std::runtime_error("Texture not found: " + name);
    }
    return this->m_textures[name];
}
sf::Font &AssetsManager::getFont(std::string name) {
    return this->m_fonts[name];
}
