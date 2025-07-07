#include "AssetsManager.h"

#include <DEFINITIONS.h>
#include <iostream>

AssetsManager::AssetsManager() : m_log(LOG_FILEPATH){}
AssetsManager::~AssetsManager() {}
void AssetsManager::loadTexture(std::string name, std::string filename) {
    sf::Texture texture;
    if (texture.loadFromFile(filename)) {
        this->m_textures[name] = texture;
        m_log.log(Logger::Level::DEBUG, "AssetManager: Texture \"" + name + "\" successfully loaded");
    } else {
        m_log.log(Logger::Level::ERROR, "AssetManager: Texture \"" + name + "\" not loaded");
    }
}
void AssetsManager::loadFont(std::string name, std::string filename) {
    sf::Font font;
    if (font.openFromFile(filename)) {
        this->m_fonts[name] = font;
    } else {
        m_log.log(Logger::Level::ERROR, "AssetManager: Font \"" + name + "\" not loaded");
    }
}

sf::Texture &AssetsManager::getTexture(std::string name) {
    if (m_textures.find(name) == m_textures.end()) {
        std::cout << "Texture not found: " << name << std::endl;
        m_log.log(Logger::Level::ERROR, "AssetManager: Texture \"" + name + "\" not found");
        throw std::runtime_error("Texture not found: " + name);
    }
    return this->m_textures[name];
}
sf::Font &AssetsManager::getFont(std::string name) {
    return this->m_fonts[name];
}
