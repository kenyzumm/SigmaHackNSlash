#include "InputManager.h"
#include <unordered_map>

// Constructor: does not require initialization
InputManager::InputManager() {}
InputManager::~InputManager() {}

// Checks if a sprite was clicked by the mouse (button and position)
bool InputManager::isSpriteClicked(sf::Sprite &object, sf::Mouse::Button button, sf::RenderWindow *window) {
    if (sf::Mouse::isButtonPressed(button)) {
        // Creates a rectangle based on the sprite's position and size
        sf::IntRect tempRect(sf::Vector2i(object.getPosition().x, object.getPosition().y),
            sf::Vector2i(object.getGlobalBounds().size));
        // Checks if the mouse position is within the sprite's rectangle
        if (tempRect.contains(sf::Mouse::getPosition(*window))) {
            return true;
        }
    }
    return false;
}

// Returns the mouse position relative to the window
sf::Vector2i InputManager::getMousePosition(sf::RenderWindow* window) {
    return sf::Mouse::getPosition(*window);
}

// Checks if a key is currently pressed
bool InputManager::isKeyPressed(sf::Keyboard::Key key) {
    return sf::Keyboard::isKeyPressed(key);
}

// Stores the previous state of keys (statically for the entire application)
static std::unordered_map<sf::Keyboard::Key, bool> previousKeyState;

// Checks if a key was just pressed (only once, not holding)
bool InputManager::isKeyJustPressed(sf::Keyboard::Key key) {
    bool currentlyPressed = sf::Keyboard::isKeyPressed(key);
    bool wasPressed = previousKeyState[key];
    previousKeyState[key] = currentlyPressed;
    return currentlyPressed && !wasPressed;
}


