#include "MainMenuState.h"
#include "GameState.h"
#include <iostream>
// Constructor: connects game data
MainMenuState::MainMenuState(GameDataRef data) : m_data(data) {}
MainMenuState::~MainMenuState() {}

// Initializes background, title, and menu button
void MainMenuState::init() {
    m_data->assets.loadTexture("MainMenu Background", MAINMENU_BACKGROUND_PATH);
    m_data->assets.loadTexture("MainMenu Title", MAINMENU_TITLE_PATH);
    m_data->assets.loadTexture("MainMenu PlayButton", MAINMENU_PLAYBUTTON_PATH);
    m_background = sf::Sprite(m_data->assets.getTexture("MainMenu Background"));
    m_title = sf::Sprite(m_data->assets.getTexture("MainMenu Title"));
    m_playButton = sf::Sprite(m_data->assets.getTexture("MainMenu PlayButton"));
    // You can set the position of the title and button

    m_background->setScale(sf::Vector2f(12,12));

    m_title->setOrigin(sf::Vector2f(m_title->getLocalBounds().size.x, 0));
    m_title->setPosition(sf::Vector2f(m_data->window->getSize().x, 0));

    // m_playButton->setOrigin(sf::Vector2f(m_playButton->getLocalBounds().size.x, m_playButton->getLocalBounds().size.y));
    m_playButton->setPosition(sf::Vector2f(m_data->window->getSize().x/2 - m_playButton->getGlobalBounds().size.x,
        m_data->window->getSize().y/2 - m_playButton->getGlobalBounds().size.y));
}

// Handles user input (closing window, clicking button)
void MainMenuState::handleInput() {
    while (const std::optional<sf::Event> event = this->m_data->window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            this->m_data->window->close();
        }
        // Checks if the "Play" button is clicked
        if (m_data->input.isSpriteClicked(*m_playButton, sf::Mouse::Button::Left, m_data->window)) {
            m_data->machine.addState(stateRef(new GameState(m_data)), true);
        }
    }
}
void MainMenuState::update(float dt) {}

// Renders background, title, and menu button
void MainMenuState::render(float dt) {
    m_data->window->clear();
    m_data->window->draw(*m_background);
    m_data->window->draw(*m_title);
    m_data->window->draw(*m_playButton);
    m_data->window->display();
}
