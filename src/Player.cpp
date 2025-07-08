#include "Player.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <cmath>

// Constructor: initializes the reference to game data and sets the movement direction to zero
Player::Player(GameDataRef data)
    : m_data(data), m_dirX(0), m_isMoving(false) {}

Player::~Player() {}

// Initializes the sprite, animations, and resets the player's movement
void Player::init() {
    m_movement.setVelocity(0, 0); // Stop the player
    m_movement.setOnGround(false); // Set that the player is not on the ground
    m_sprite.emplace(m_data->assets.getTexture("Player")); // Load the player texture
    if (m_sprite) {
        m_animation.setSprite(&(*m_sprite)); // Connect the animation to the sprite
        m_sprite->setOrigin({32.f, 64.f}); // Set the bottom center as the reference point
        m_sprite->setPosition({100.f, 200.f}); // Initial position
    }
    m_animation.setFrameData(64, 64, 0, 0); // Animation frame size
    // Add animations for different states
    m_animation.addAnimation(AnimState::Idle, 0, 0, 0, 1.0f, 9);
    m_animation.addAnimation(AnimState::Run, 3, 1, 8, 0.1f, 9);
    m_animation.addAnimation(AnimState::Jump, 2, 0, 0, 0.2f, 9);
    m_animation.addAnimation(AnimState::Fall, 1, 0, 0, 0.2f, 9);
    m_animation.setAnimation(AnimState::Idle); // Set the initial animation
}

// Handles keyboard input and sets the movement direction and jump
void Player::handleInput() {
    // Direction: D (right) = 1, A (left) = -1, none = 0
    m_dirX = (int)(m_data->input.isKeyPressed(sf::Keyboard::Key::D)) -
             (int)(m_data->input.isKeyPressed(sf::Keyboard::Key::A));
    if (m_data->input.isKeyPressed(sf::Keyboard::Key::Space)) {
        m_movement.jump(); // Jump
    }
}

// Updates the player's state: movement, collisions, animation
void Player::update(float dt, TileMap* tileMap) {
    handleInput(); // First handle input
    m_isMoving = (m_dirX != 0.0f); // Is the player moving
    m_movement.update(m_dirX, dt); // Update player movement physics
    if (m_sprite) {
        // Move the sprite based on velocity
        sf::Vector2f pos = m_sprite->getPosition();
        pos.x += m_movement.getVelocityX() * dt;
        pos.y += m_movement.getVelocityY() * dt;
        // Check for collisions with tiles below
        if (tileMap) {
            int tileSize = tileMap->getTileSize();
            float feetY = pos.y;
            int tileX = static_cast<int>(pos.x / tileSize);
            int tileY = static_cast<int>(feetY / tileSize);
            if (tileMap->isCollidable(tileX, tileY)) {
                // If there is a collidable tile below, stop falling
                m_movement.setVelocity(m_movement.getVelocityX(), 0);
                m_movement.setOnGround(true);
            } else {
                m_movement.setOnGround(false);
            }
        }
        // Set the sprite scale (mirror reflection) based on direction
        float vx = m_movement.getVelocityX();
        m_sprite->setScale({vx < 0 ? -1.f : 1.f, 1.f});
        m_sprite->setPosition(pos);
    }
    // Select animation based on movement state and ground contact
    float vx = m_movement.getVelocityX();
    float vy = m_movement.getVelocityY();
    AnimState newState;
    if (!m_movement.getOnGround()) {
        newState = (vy < 0 ? AnimState::Jump : AnimState::Fall);
    } else if (m_dirX != 0) {
        newState = AnimState::Run;
    } else {
        newState = AnimState::Idle;
    }
    if (m_animation.getCurrentState() != newState) {
        m_animation.setAnimation(newState);
    }
    m_animation.update(dt); // Move to the next animation frame
}

// Renders the player sprite on the screen
void Player::render(float dt) {
    if (m_data && m_data->window && m_sprite) {
        m_data->window->draw(*m_sprite);
    }
}

// Sets the player's position and resets velocity
void Player::setPosition(float x, float y) {
    if (m_sprite) {
        m_sprite->setPosition({x, y});
        m_movement.setVelocity(0, 0);
    }
}

// Returns the current X position of the player
float Player::getX() const { return m_sprite ? m_sprite->getPosition().x : 0.f; }
// Returns the current Y position of the player
float Player::getY() const { return m_sprite ? m_sprite->getPosition().y : 0.f; }