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
    // Loads texture from file and saves it under a name
    void loadTexture(std::string name, std::string filename);
    // Loads font from file and saves it under a name
    void loadFont(std::string name, std::string filename);

    // Returns a reference to the font with the given name
    sf::Font &getFont(std::string name);
    // Returns a reference to the texture with the given name
    sf::Texture &getTexture(std::string name);
};

#endif //ASSETSMANAGER_H
