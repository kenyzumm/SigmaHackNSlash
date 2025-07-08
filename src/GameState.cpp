#include "GameState.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
GameState::GameState(GameDataRef data) : m_data(data), m_player(nullptr) {}

GameState::~GameState() {
    delete m_player;
    delete m_tileMap;
}

sf::RenderWindow* g_window = nullptr;

void GameState::init() {
    // Load background
    m_data->assets.loadTexture("GameState Background", GAMESTATE_BACKGROUND_PATH);
    m_background = sf::Sprite(this->m_data->assets.getTexture("GameState Background"));
    
    // Load player texture
    m_data->assets.loadTexture("Player", PLAYER_TEXTURE_PATH);
    
    // Initialize player
    m_player = new Player(m_data);
    m_tileMap = new TileMap(100, 100, 32);
    g_window = m_data->window;

    // Dodaj prosty "grunt" pod graczem
    for (int x = 3; x <= 6; ++x) {
        m_tileMap->setTile(x, 7, TILE_SOLID, true);
    }
    // Ustaw gracza dokładnie nad kafelkiem (środek dolnej krawędzi sprite'a na środku kafelka 4,7)
    float tileSize = 32.f;
    float spriteHeight = 64.f;
    float playerX = (4 + 0.5f) * tileSize;
    float playerY = (7 + 1) * tileSize - (spriteHeight - tileSize);
    if (m_player) m_player->setPosition(playerX, playerY);
    std::cout << "Player start pos: x=" << playerX << " y=" << playerY << std::endl;
    m_player->init();
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
    if (m_player) m_player->update(dt, m_tileMap);
}

void GameState::render(float dt) {
    m_data->window->clear();
    if (m_tileMap) m_tileMap->render();
    // Draw background (za gruntem)
    if (m_background.has_value()) {
        m_data->window->draw(*m_background);
    }
    if (m_player) m_player->render(dt);
    m_data->window->display();
}

