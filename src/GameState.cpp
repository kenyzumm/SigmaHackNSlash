#include "GameState.h"

GameState::GameState(GameDataRef data) : m_data(data), m_player(nullptr) {}

GameState::~GameState() {
    delete m_player;
    delete m_tileMap;
}

void GameState::init() {
    // Load background
    m_data->assets.loadTexture("GameState Background", GAMESTATE_BACKGROUND_PATH);
    m_background = sf::Sprite(this->m_data->assets.getTexture("GameState Background"));
    
    // Load player texture
    m_data->assets.loadTexture("Player", PLAYER_TEXTURE_PATH);
    
    // Initialize player
    m_player = new Player(m_data);
    m_tileMap = new TileMap(100, 100, 32);
    m_player->init();
    
    
       
    // Initialize tile map (simple ground for now)
 
}   

void GameState::handleInput() {
    // Reset input flags
    
    
    while (const std::optional<sf::Event> event = this->m_data->window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            this->m_data->window->close();
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace)) {
        this->m_data->window->close();
    }
}

void GameState::update(float dt) {
    if (m_player) m_player->update(dt);
}

void GameState::render(float dt) {
    m_data->window->clear();
    
    // Draw background
    if (m_background.has_value()) {
        m_data->window->draw(*m_background);
    }
    if (m_player) m_player->render(dt);
    m_data->window->display();
}

