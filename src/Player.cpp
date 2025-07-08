#include "Player.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
Player::Player(GameDataRef data)
    : m_data(data), m_dirX(0), m_dirY(0), m_isMoving(false), m_state("idle") {}

Player::~Player() {}

void Player::init() {
    m_state = "idle";
    m_movement.setVelocity(0, 0);
    m_movement.setOnGround(false);
    m_sprite.emplace(m_data->assets.getTexture("Player"));
    m_sprite->setPosition({100.0f, 100.0f});
    m_collision.posX = m_sprite->getPosition().x;
    m_collision.posY = m_sprite->getPosition().y;
    // Integracja animacji
    if (m_sprite) {
        m_animation.setSprite(&(*m_sprite));
    }
    m_animation.setFrameData(64, 64, 0, 0); // przykładowe wartości: szerokość, wysokość, startX, startY
    m_animation.addAnimation("idle", 0, 3, 0.15f); // przykładowa animacja: klatki 0-3
    m_animation.setAnimation("idle");
}

void Player::handleInput() {
    // Przykładowa obsługa wejścia (do rozbudowy pod konkretny system inputu)
    // np. pobierz dane z m_data->input
    // Ustaw m_dirX, m_dirY na podstawie wejścia
    // Przykład: jeśli skok
    // if (jumpKeyPressed) m_movement.jump();
}

void Player::move(float dirX, float dirY, float dt) {
    m_dirX = dirX;
    m_dirY = dirY;
    m_isMoving = (dirX != 0.0f || dirY != 0.0f);
    m_movement.move(dirX, dirY, dt);
}

void Player::update(float dt) {
    handleInput();
    if (m_isMoving) {
        move(m_dirX, m_dirY, dt);
        m_state = "run";
    } else {
        m_state = "idle";
    }
    m_movement.update(dt);
    // Aktualizacja pozycji na podstawie Movement
    if (m_sprite) {
        sf::Vector2f pos = m_sprite->getPosition();
        pos.x += m_movement.getVelocityX() * dt;
        pos.y += m_movement.getVelocityY() * dt;
        m_sprite->setPosition(pos);
        // Przykład: jeśli gracz dotknął ziemi
        // if (pos.y >= groundLevel) {
        //     pos.y = groundLevel;
        //     m_movement.setOnGround(true);
        //     m_sprite->setPosition(pos);
        // }
        m_collision.posX = pos.x;
        m_collision.posY = pos.y;
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
        m_sprite->setPosition({x, y});
        m_movement.setVelocity(0, 0);
        m_collision.posX = x;
        m_collision.posY = y;
    }
}

float Player::getX() const { return m_sprite ? m_sprite->getPosition().x : 0.f; }
float Player::getY() const { return m_sprite ? m_sprite->getPosition().y : 0.f; }

Collision& Player::getCollision() { return m_collision; }