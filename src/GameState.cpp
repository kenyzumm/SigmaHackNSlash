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

    // Generate a more complex map layout
    generateMap();

    // Set the player exactly on the tile (since sprite origin is at bottom center)
    float tileSize = 32.f;
    float playerX = (4 + 0.5f) * tileSize; // Center of tile 4
    float playerY = 7 * tileSize; // Top of tile 7 (sprite origin is at bottom)
    if (m_player) m_player->setPosition(playerX, playerY);
    m_player->init();
}

/**
 * @brief Generates a more complex map layout with multiple platforms, gaps, and obstacles.
 * This function creates several platforms at different heights, adds gaps (holes), and vertical columns as obstacles.
 * It demonstrates how to procedurally generate a simple but varied level for the player to traverse.
 * All tiles are set using setTile(x, y, TILE_SOLID, true).
 */
void GameState::generateMap() {
    if (!m_tileMap) return;
    // Main ground platform (with gaps)
    for (int x = 0; x < 20; ++x) {
        if (x == 5 || x == 12) continue; // Create gaps at x=5 and x=12
        m_tileMap->setTile(x, 15, TILE_SOLID, true);
    }
    // Floating platform 1
    for (int x = 3; x < 8; ++x) {
        m_tileMap->setTile(x, 10, TILE_SOLID, true);
    }
    // Floating platform 2 (with a gap)
    for (int x = 12; x < 18; ++x) {
        if (x == 15) continue; // Gap at x=15
        m_tileMap->setTile(x, 7, TILE_SOLID, true);
    }
    // Small column obstacles
    for (int y = 14; y > 12; --y) {
        m_tileMap->setTile(9, y, TILE_SOLID, true);
    }
    for (int y = 14; y > 11; --y) {
        m_tileMap->setTile(17, y, TILE_SOLID, true);
    }
    // Stairs
    for (int i = 0; i < 4; ++i) {
        m_tileMap->setTile(20 + i, 15 - i, TILE_SOLID, true);
    }
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
    // Strzał pociskiem tylko na jedno kliknięcie LPM
    bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    if (isMousePressed && !wasMousePressedLastFrame && m_player) {
        sf::Vector2f playerPos(m_player->getX(), m_player->getY() - 32);
        sf::Vector2i mousePixel = sf::Mouse::getPosition(*m_data->window);
        sf::Vector2f mouseWorld = m_data->window->mapPixelToCoords(mousePixel);
        sf::Vector2f direction = mouseWorld - playerPos;
        float len = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (len > 0.01f) direction /= len;
        float bulletSpeed = 1000.f;
        sf::Vector2f velocity = direction * bulletSpeed;
        m_bullets.push_back(new Bullet(playerPos, velocity));
    }
    wasMousePressedLastFrame = isMousePressed;
}

// Updates game logic: calls player and map updates
void GameState::update(float dt) {
    if (m_player) m_player->update(dt, m_tileMap);
    if (m_hud) m_hud->update(dt);

    // Update bullets and remove those that go off screen OR hit solid tiles
    auto it = m_bullets.begin();
    sf::Vector2u winSize = m_data->window->getSize();
    while (it != m_bullets.end()) {
        Bullet* bullet = *it;
        bullet->update(dt);
        sf::Vector2f pos = bullet->getPosition();
        
        // Remove bullets that go off screen boundaries OR hit solid tiles
        if (pos.x < 0 || pos.x > winSize.x || pos.y < 0 || pos.y > winSize.y || 
            bullet->checkTileCollision(m_tileMap)) {
            delete bullet;
            it = m_bullets.erase(it);
        } else {
            ++it;
        }
    }
}

// Renders background, map, bullets, and player to the screen
void GameState::render(float dt) {
    m_data->window->clear();
    if (m_tileMap) m_tileMap->render(m_data->window);
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

