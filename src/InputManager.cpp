#include "InputManager.h"

InputManager::InputManager() : m_log(LOG_FILEPATH) {}
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
sf::Vector2i InputManager::getMousePosition(sf::RenderWindow* window) {
    return sf::Mouse::getPosition(*window);
}


