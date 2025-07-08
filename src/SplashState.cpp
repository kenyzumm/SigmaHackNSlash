#include "SplashState.h"

#include <iostream>

#include "MainMenuState.h"

// Constructor: connects game data
SplashState::SplashState(GameDataRef data) : m_data(data) {}
SplashState::~SplashState() {}

// Initializes background and sets scale
void SplashState::init() {
    m_data->assets.loadTexture("SplashState Background", SPLASHSTATE_BACKGROUND_PATH);
    m_data->assets.loadTexture("SplashState Title", SPLASHSTATE_TITLE_PATH);

    m_background = sf::Sprite(this->m_data->assets.getTexture("SplashState Background"));
    m_background->setScale(sf::Vector2f(12, 12));

    m_title = sf::Sprite(this->m_data->assets.getTexture("SplashState Title"));
    m_title->setOrigin(sf::Vector2f(m_title->getLocalBounds().size.x / 2, m_title->getLocalBounds().size.y / 2));
    m_title->setPosition(sf::Vector2f(m_data->window->getSize().x / 2, m_data->window->getSize().y / 2));
}

// Handles user input (closing window)
void SplashState::handleInput() {
    while (const std::optional<sf::Event> event = this->m_data->window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            this->m_data->window->close();
        }
    }
}

// After a certain time, it transitions to the main menu
void SplashState::update(float dt) {
    if (m_clock.getElapsedTime().asSeconds() > SPLASHSTATE_SHOWTIME) {
        m_data->machine.addState(stateRef(new MainMenuState(m_data)), true);
    }
}

// Renders the splash background on the screen
void SplashState::render(float dt) {
    m_data->window->clear();
    m_data->window->draw(*m_background);
    m_data->window->draw(*m_title);
    m_data->window->display();
}