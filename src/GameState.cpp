#include "GameState.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

// Constructor: initializes player and map pointers
GameState::GameState(GameDataRef data) : m_data(data), m_player(nullptr), m_log("GameStateLogs.txt") {}

GameState::~GameState() {
    delete m_player;
    delete m_tileMap;
}

// Initializes game state: loads background, textures, creates player and map, sets initial position
void GameState::init() {
    m_data->assets.loadTexture("GameState Background", GAMESTATE_BACKGROUND_PATH);
    m_background = sf::Sprite(this->m_data->assets.getTexture("GameState Background"));
    m_data->assets.loadTexture("Player", PLAYER_TEXTURE_PATH);

    m_player = new Player(m_data);
    m_tileMap = new TileMap(100, 100, 32);

    // Error handling if m_player or m_tilemap are nullptr
    if (!m_player) {
        LOG_ERROR(m_log, "Failed to create player");
    }
    if (!m_tileMap) {
        LOG_ERROR(m_log, "Failed to create tile map");
    }


    // DEBUG
    // Add a simple "ground" under the player
    for (int x = 3; x <= 9; ++x) {
        m_tileMap->setTile(x, 7, TILE_SOLID, true);
    }
    for (int x = 3; x <= 9; ++x) {
        m_tileMap->setTile(x, 12, TILE_SOLID, true);
    }
    // Set the player exactly on the tile (since sprite origin is at bottom center)
    float tileSize = 32.f;
    float playerX = (4 + 0.5f) * tileSize; // Center of tile 4
    float playerY = 7 * tileSize; // Top of tile 7 (sprite origin is at bottom)
    if (m_player) m_player->setPosition(playerX, playerY);
    m_player->init();
}   

// Handles user input (closing window)
void GameState::handleInput() {
    while (const std::optional<sf::Event> event = this->m_data->window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            this->m_data->window->close();
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace)) {
        this->m_data->window->close();
    }
}

// Updates game logic: calls player and map updates
void GameState::update(float dt) {
    if (m_player) m_player->update(dt, m_tileMap);
}

// Renders background, map, and player to the screen
void GameState::render(float dt) {
    m_data->window->clear();
    if (m_tileMap) m_tileMap->render(m_data->window);
    if (m_background.has_value()) {
        m_data->window->draw(*m_background);
    }
    if (m_player) m_player->render(dt);
    m_data->window->display();
}

