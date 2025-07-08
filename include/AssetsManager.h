#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <map>
#include <SFML/Graphics.hpp>
#include "Logger.h"

// Class managing game resources (textures, fonts)
class AssetsManager {
    std::map<std::string, sf::Texture> m_textures; // Texture map
    std::map<std::string, sf::Font> m_fonts;       // Font map
    Logger m_log;                                 // Logger for loading errors
public:
    AssetsManager();
    ~AssetsManager();
    // Loaders
    void loadTexture(std::string name, std::string filename);
    void loadFont(std::string name, std::string filename);

    // Getters
    sf::Font &getFont(std::string name);
    sf::Texture &getTexture(std::string name);
};

#endif //ASSETSMANAGER_H
