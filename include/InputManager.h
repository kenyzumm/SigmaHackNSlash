#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <SFML/Graphics.hpp>
#include <DEFINITIONS.h>
#include "Logger.h"

// Class responsible for user input (keyboard, mouse)
class InputManager {
public:
    InputManager();
    ~InputManager();

    sf::Vector2i getMousePosition(sf::RenderWindow* window);

    // Checkers
    // Checks if the sprite was clicked by the mouse
    bool isSpriteClicked(sf::Sprite &object, sf::Mouse::Button button, sf::RenderWindow* window);
    // Checks if a key is pressed
    bool isKeyPressed(sf::Keyboard::Key key);
    // Checks if a key was just pressed (only once)
    bool isKeyJustPressed(sf::Keyboard::Key key);
};
#endif //INPUTMANAGER_H
