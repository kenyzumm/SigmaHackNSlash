#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <map>
#include <SFML/Graphics.hpp>
#include "Logger.h"

class AssetsManager {
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, sf::Font> m_fonts;
    Logger m_log;
public:
    AssetsManager();
    ~AssetsManager();
    // Loading resources
    void loadTexture(std::string name, std::string filename);
    void loadFont(std::string name, std::string filename);

    // Getting resources
    sf::Font &getFont(std::string name);
    sf::Texture &getTexture(std::string name);
};

#endif //ASSETSMANAGER_H
