#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <SFML/Graphics.hpp>
#include <DEFINITIONS.h>
#include "Logger.h"

class InputManager {
    Logger m_log;
public:

    InputManager();
    ~InputManager();
    bool isSpriteClicked(sf::Sprite &object, sf::Mouse::Button button, sf::RenderWindow* window);
    sf::Vector2i getMousePosition(sf::RenderWindow* window);
    bool isKeyPressed(sf::Keyboard::Key key);
    bool isKeyJustPressed(sf::Keyboard::Key key);
};



#endif //INPUTMANAGER_H
