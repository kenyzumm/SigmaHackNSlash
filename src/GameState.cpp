#include "GameState.h"
#include <iostream>

GameState::GameState(GameDataRef data) : m_data(data) {}

GameState::~GameState() {}

void GameState::init() {
    // Load background
    m_data->assets.loadTexture("GameState Background", GAMESTATE_BACKGROUND_PATH);
    m_background = sf::Sprite(this->m_data->assets.getTexture("GameState Background"));
    
    // Load player texture
    m_data->assets.loadTexture("Player", PLAYER_TEXTURE_PATH);
    
    // Initialize player
    
    
       
    // Initialize tile map (simple ground for now)
 
}   

void GameState::handleInput() {
    // Reset input flags
    
    
    while (const std::optional<sf::Event> event = this->m_data->window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            this->m_data->window->close();
        }
    }
    
}

void GameState::update(float dt) {}

void GameState::render(float dt) {
    m_data->window->clear();
    
    // Draw background
    if (m_background.has_value()) {
        m_data->window->draw(*m_background);
    }

    m_data->window->display();
}

