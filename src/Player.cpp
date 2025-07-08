#include "Player.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <cmath>

Player::Player(GameDataRef data)
    : m_data(data), m_dirX(0), m_dirY(0), m_isMoving(false), m_state(AnimState::Idle) {}

Player::~Player() {}

void Player::init() {
    m_state = AnimState::Idle;
    m_movement.setVelocity(0, 0);
    m_movement.setOnGround(false);
    m_sprite.emplace(m_data->assets.getTexture("Player"));
    m_sprite->setPosition({100.0f, 100.0f});
    m_collision.posX = m_sprite->getPosition().x;
    m_collision.posY = m_sprite->getPosition().y;
    // Integracja animacji
    if (m_sprite) {
        m_animation.setSprite(&(*m_sprite));
        m_sprite->setOrigin({32.f, 64.f}); // środek dolnej krawędzi klatki 64x64
        m_sprite->setPosition({100.f, 200.f});
    }
    m_animation.setFrameData(64, 64, 0, 0); // rozmiar klatki
    // Idle: rząd 3, kolumna 0
    m_animation.addAnimation(AnimState::Idle, 0, 0, 0, 1.0f, 9);
    // Run: rząd 3, kolumny 1-8
    m_animation.addAnimation(AnimState::Run, 3, 1, 8, 0.1f, 9);
    // Jump: rząd 2, kolumna 0
    m_animation.addAnimation(AnimState::Jump, 2, 0, 0, 0.2f, 9);
    // Fall: rząd 2, kolumna 0 (możesz zmienić na inną jeśli masz)
    m_animation.addAnimation(AnimState::Fall, 1, 0, 0, 0.2f, 9);
    m_animation.setAnimation(AnimState::Idle);
}

void Player::handleInput() {
    m_dirX = 0;
    m_dirY = 0;
    // Przykładowa obsługa wejścia (do rozbudowy pod konkretny system inputu)
    // np. pobierz dane z m_data->input
    // Ustaw m_dirX, m_dirY na podstawie wejścia
    // Przykład: jeśli skok
    // if (jumpKeyPressed) m_movement.jump();

    if (m_data->input.isKeyPressed(sf::Keyboard::Key::A)) {
        m_dirX = -1;
    }
    if (m_data->input.isKeyPressed(sf::Keyboard::Key::D)) {
        m_dirX = 1;
    }
    if (m_data->input.isKeyPressed(sf::Keyboard::Key::Space)) {
        m_movement.jump();
    }
}

void Player::move(float dirX, float dirY, float dt) {
    m_isMoving = (dirX != 0.0f || dirY != 0.0f);
    m_movement.move(dirX, dirY, dt);
}

void Player::update(float dt, TileMap* tileMap) {
    handleInput();
    move(m_dirX, m_dirY, dt);
    m_state = (m_isMoving ? AnimState::Run : AnimState::Idle);
    m_movement.update(dt);
    // Aktualizacja pozycji na podstawie Movement
    if (m_sprite) {
        sf::Vector2f pos = m_sprite->getPosition();
        pos.x += m_movement.getVelocityX() * dt;
        pos.y += m_movement.getVelocityY() * dt;
        // Sprawdź kafelek pod nogami
        if (tileMap) {
            int tileSize = tileMap->getTileSize();
            float feetY = pos.y;
            int tileX = static_cast<int>(pos.x / tileSize);
            int tileY = static_cast<int>(feetY / tileSize);
            if (tileMap->isCollidable(tileX, tileY)) {
                pos.y = tileY * tileSize;
                m_movement.setVelocity(m_movement.getVelocityX(), 0);
                m_movement.setOnGround(true);
            } else {
                m_movement.setOnGround(false);
            }
        }
        float vx = m_movement.getVelocityX();
        if (vx < 0) m_sprite->setScale({-1.f, 1.f});
        else m_sprite->setScale({1.f, 1.f});
        m_sprite->setPosition(pos);
        std::cout << "[update] Sprite pos: x=" << pos.x << " y=" << pos.y << std::endl;
        m_collision.posX = pos.x;
        m_collision.posY = pos.y;
    }
    // Wybór animacji na podstawie ruchu i stanu
    float vx = m_movement.getVelocityX();
    float vy = m_movement.getVelocityY();
    if (!m_movement.getOnGround()) {
        if (vy < 0) m_animation.setAnimation(AnimState::Jump);
        else m_animation.setAnimation(AnimState::Fall);
    } else if (std::abs(vx) > 1.0f) {
        m_animation.setAnimation(AnimState::Run);
    } else {
        m_animation.setAnimation(AnimState::Idle);
    }
    m_animation.update(dt);
}

void Player::render(float dt) {
    if (m_data && m_data->window && m_sprite) {
        m_data->window->draw(*m_sprite);
    }
}

void Player::setPosition(float x, float y) {
    if (m_sprite) {
        // Ustaw środek dolnej krawędzi na (x, y)
        m_sprite->setPosition({x, y});
        std::cout << "[setPosition] Sprite pos: x=" << x << " y=" << y << std::endl;
        m_movement.setVelocity(0, 0);
        m_collision.posX = x;
        m_collision.posY = y;
    }
}

float Player::getX() const { return m_sprite ? m_sprite->getPosition().x : 0.f; }
float Player::getY() const { return m_sprite ? m_sprite->getPosition().y : 0.f; }

Collision& Player::getCollision() { return m_collision; }