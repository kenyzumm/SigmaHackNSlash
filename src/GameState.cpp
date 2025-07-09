#include "GameState.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <cmath>

// Constructor: initializes player and map pointers
GameState::GameState(GameDataRef data) : m_data(data), m_player(nullptr), m_log("GameStateLogs.txt") {}

GameState::~GameState() {
    delete m_player;
    delete m_tileMap;
    delete m_hud;
    // Usuwanie wszystkich pocisków
    for (auto bullet : m_bullets) {
        delete bullet;
    }
    m_bullets.clear();
}

// Initializes game state: loads background, textures, creates player and map, sets initial position
void GameState::init() {
    m_data->assets.loadTexture("GameState Background", GAMESTATE_BACKGROUND_PATH);
    m_background = sf::Sprite(this->m_data->assets.getTexture("GameState Background"));
    m_data->assets.loadTexture("Player", PLAYER_TEXTURE_PATH);
    m_data->assets.loadTexture("HUD Hearth", HUD_HEALTH_BAR_PATH);
    m_data->assets.loadFont("Arial", ARIAL_FONT_PATH);

    m_player = new Player(m_data);
    m_tileMap = new TileMap(100, 100, 32);
    m_hud = new HUD(m_data);

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
        m_tileMap->setTile(x, 10, TILE_SOLID, true);
    }
    // Set the player exactly on the tile (since sprite origin is at bottom center)
    float tileSize = 32.f;
    float playerX = (4 + 0.5f) * tileSize; // Center of tile 4
    float playerY = 7 * tileSize; // Top of tile 7 (sprite origin is at bottom)
    if (m_player) m_player->setPosition(playerX, playerY);
    m_player->init();
}   

// Flaga do wykrywania pojedynczego kliknięcia myszy
static bool wasMousePressedLastFrame = false;

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
    // Strzał pociskiem tylko na jedBullet::Bullet() {
    m_shape.setRadius(5);
    m_shape.setFillColor(sf::Color::White);
    m_shape.setPosition({0, 0});
    m_speed = 1000;
    m_direction = 0;
    m_damage = 10;
    m_range = 1000;
}et(playerPos, velocity));
    }
    wasMousePressedLastFrame = isMousePressed;
}

// Updates game logic: calls player and map updates
void GameState::update(float dt) {
    if (m_player) m_player->update(dt, m_tileMap);
    if (m_hud) m_hud->update(dt);

    // Aktualizacja pocisków i usuwanie tych poza ekranem
    auto it = m_bullets.begin();
    sf::Vector2u winSize = m_data->window->getSize();
    while (it != m_bullets.end()) {
        Bullet* bullet = *it;
        bullet->update(dt);
        sf::Vector2f pos = bullet->getBullet::Bullet() {
            m_shape.setRadius(5);
            m_shape.setFillColor(sf::Color::White);
            m_shape.setPosition({0, 0});
            m_speed = 1000;
            m_direction = 0;
            m_damage = 10;
            m_range = 1000;
        }_data->window);
    /*if (m_background.has_value()) {
        m_data->window->draw(*m_background);
    }
    */

    // Rysowanie pocisków
    for (auto bullet : m_bullets) {
        bullet->draw(m_data->window);
    }

    if (m_player) m_player->render(dt);
    if (m_hud) m_hud->draw();
    m_data->window->display();
}

