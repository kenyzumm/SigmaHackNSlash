#include "SplashState.h"

#include <iostream>

#include "MainMenuState.h"

SplashState::SplashState(GameDataRef data) : m_data(data) {}
SplashState::~SplashState() {}
void SplashState::init() {
    m_data->assets.loadTexture("SplashState Background", SPLASHSTATE_BACKGROUND_PATH);
    m_background = sf::Sprite(this->m_data->assets.getTexture("SplashState Background"));
    m_background->setScale(sf::Vector2f(12, 12));
}
void SplashState::handleInput() {
    while (const std::optional<sf::Event> event = this->m_data->window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            this->m_data->window->close();
        }
    }
}
void SplashState::update(float dt) {
    if (m_clock.getElapsedTime().asSeconds() > SPLASHSTATE_SHOWTIME) {
        m_data->machine.addState(stateRef(new MainMenuState(m_data)), true);
    }
}
void SplashState::render(float dt) {
    m_data->window->clear();
    m_data->window->draw(*m_background);
    m_data->window->display();
}