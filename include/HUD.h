#ifndef HUD_H
#define HUD_H

#include "SFML/Graphics.hpp"
#include <Game.h>

class HUD {
    GameDataRef m_data;
    std::vector<sf::Sprite> m_healthHearthVector;
    std::optional<sf::Sprite> m_weaponBar;
    std::optional<sf::Text> m_dashCooldown;
    sf::Font m_font;


    public:
        HUD(GameDataRef data);
        ~HUD();

        void update(float dt);
        void draw();
};

#endif // HUD_H