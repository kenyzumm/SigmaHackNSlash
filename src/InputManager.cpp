#include "InputManager.h"
#include <unordered_map>

InputManager::InputManager() : m_log("InputManagerLogs.txt") {
    
}
InputManager::~InputManager() {}
bool InputManager::isSpriteClicked(sf::Sprite &object, sf::Mouse::Button button, sf::RenderWindow *window) {
    if (sf::Mouse::isButtonPressed(button)) {
        sf::IntRect tempRect(sf::Vector2i(object.getPosition().x, object.getPosition().y),
            sf::Vector2i(object.getGlobalBounds().size));
        if (tempRect.contains(sf::Mouse::getPosition(*window))) {
            return true;
        }
    }
    return false;
}
bool isButtonClicked() {}
sf::Vector2i InputManager::getMousePosition(sf::RenderWindow* window) {
    return sf::Mouse::getPosition(*window);
}

bool InputManager::isKeyPressed(sf::Keyboard::Key key) {
    return sf::Keyboard::isKeyPressed(key);
}

static std::unordered_map<sf::Keyboard::Key, bool> previousKeyState;

bool InputManager::isKeyJustPressed(sf::Keyboard::Key key) {
    bool currentlyPressed = sf::Keyboard::isKeyPressed(key);
    bool wasPressed = previousKeyState[key];
    previousKeyState[key] = currentlyPressed;
    return currentlyPressed && !wasPressed;
}


