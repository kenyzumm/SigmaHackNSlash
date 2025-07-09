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
        // m_sprite->setPosition({100.f, 200.f}); // Initial position (REMOVED)
    }
    m_animation.setFrameData(64, 64, 0, 0); // Animation frame size
    // Add animations for different states
    m_animation.addAnimation(AnimState::Idle, 2, 0, 0, 1.0f, 9);
    m_animation.addAnimation(AnimState::Run, 3, 1, 8, 0.1f, 9);
    m_animation.addAnimation(AnimState::Jump, 2, 0, 0, 0.2f, 9);
    m_animation.addAnimation(AnimState::Fall, 2, 0, 0, 0.2f, 9);
    m_animation.setAnimation(AnimState::Idle); // Set the initial animation
}

// Handles keyboard input and sets the movement direction, jump, and dash
/**
 * Handles keyboard input for movement, jumping, double jumping, and dashing.
 * Dash can now be performed both on the ground and in the air, but is always limited by the dash cooldown.
 * The player must be moving left or right (A or D) and dash is only triggered on LShift key press.
 * Jump and double jump logic is unchanged.
 */
void Player::handleInput() {
    // Direction: D (right) = 1, A (left) = -1, none = 0
    m_dirX = (int)(m_data->input.isKeyPressed(sf::Keyboard::Key::D)) -
             (int)(m_data->input.isKeyPressed(sf::Keyboard::Key::A));
    
    // Dash: only if moving left or right, and dash is available (ground or air)
    if (m_data->input.isKeyJustPressed(sf::Keyboard::Key::LShift)) {
        if (m_dirX != 0 && m_movement.canDash()) {
            m_movement.startDash(m_dirX);
        }
    }
    
    // Handle jump and double jump with Space key (only on key press, not hold)
    if (m_data->input.isKeyJustPressed(sf::Keyboard::Key::Space)) {
        if (m_movement.getOnGround()) {
            // First jump when on ground
            m_movement.jump();
        } else if (!m_movement.getHasDoubleJumped() && m_movement.getCanDoubleJump()) {
            // Double jump when in air and haven't used double jump yet
            m_movement.doubleJump();
        }
    }
}

// Updates the player's state: movement, collisions, animation
void Player::update(float dt, TileMap* tileMap) {
    handleInput();
    m_isMoving = (m_dirX != 0.0f);
    m_movement.update(m_dirX, dt);

    if (m_sprite) {
        sf::Vector2f pos = m_sprite->getPosition();
        float vx = m_movement.getVelocityX();
        float vy = m_movement.getVelocityY();
        float nextX = pos.x;
        float nextY = pos.y;
        int tileSize = tileMap ? tileMap->getTileSize() : 32;
        float playerWidth = 64.f;
        float playerHeight = 64.f;
        float left, right, top, bottom;
        // --- Vertical movement and collision (Y axis) ---
        nextY += vy * dt;
        left = nextX - playerWidth / 2.f;
        right = nextX + playerWidth / 2.f;
        top = nextY - playerHeight;
        bottom = nextY;
        if (tileMap) {
            // Sprawdzaj 3 punkty: lewy, środek, prawy
            float pointsX[3] = {left + 1, nextX, right - 1};
            if (vy > 0) { // Falling
                int tileY = static_cast<int>(bottom / tileSize);
                for (float px : pointsX) {
                    int tileX = static_cast<int>(px / tileSize);
                    if (tileMap->isCollidable(tileX, tileY)) {
                        nextY = tileY * tileSize;
                        vy = 0;
                        break;
                    }
                }
            } else if (vy < 0) { // Jumping
                int tileY = static_cast<int>((top) / tileSize);
                for (float px : pointsX) {
                    int tileX = static_cast<int>(px / tileSize);
                    if (tileMap->isCollidable(tileX, tileY)) {
                        nextY = (tileY + 1) * tileSize + playerHeight;
                        vy = 0;
                        break;
                    }
                }
            }
        }
        // --- Horizontal movement and collision (X axis) ---
        nextX += vx * dt;
        left = nextX - playerWidth / 2.f;
        right = nextX + playerWidth / 2.f;
        top = nextY - playerHeight;
        bottom = nextY;
        if (tileMap) {
            if (vx > 0) { // Moving right
                int tileX = static_cast<int>((right) / tileSize);
                int tileYTop = static_cast<int>((top + 1) / tileSize);
                int tileYBottom = static_cast<int>((bottom - 1) / tileSize);
                if (tileMap->isCollidable(tileX, tileYTop) || tileMap->isCollidable(tileX, tileYBottom)) {
                    nextX = tileX * tileSize - playerWidth / 2.f;
                    vx = 0;
                }
            } else if (vx < 0) { // Moving left
                int tileX = static_cast<int>((left) / tileSize);
                int tileYTop = static_cast<int>((top + 1) / tileSize);
                int tileYBottom = static_cast<int>((bottom - 1) / tileSize);
                if (tileMap->isCollidable(tileX, tileYTop) || tileMap->isCollidable(tileX, tileYBottom)) {
                    nextX = (tileX + 1) * tileSize + playerWidth / 2.f;
                    vx = 0;
                }
            }
        }
        // --- Check if player is on ground (after all movement) ---
        bool onGround = false;
        if (tileMap) {
            float feetY = nextY + 1; // 1px below feet
            float pointsX[3] = {nextX - playerWidth / 2.f + 1, nextX, nextX + playerWidth / 2.f - 1};
            int tileY = static_cast<int>(feetY / tileSize);
            for (float px : pointsX) {
                int tileX = static_cast<int>(px / tileSize);
                if (tileMap->isCollidable(tileX, tileY)) {
                    onGround = true;
                    break;
                }
            }
        }
        m_movement.setVelocity(vx, vy);
        m_movement.setOnGround(onGround);
        m_sprite->setScale({vx < 0 ? -1.f : 1.f, 1.f});
        m_sprite->setPosition({nextX, nextY});
    }
    // --- Animation state selection ---
    float vx = m_movement.getVelocityX();
    float vy = m_movement.getVelocityY();
    AnimState newState;
    if (m_movement.getOnGround()) {
        if (m_isMoving) newState = AnimState::Run;
        else newState = AnimState::Idle;
    } else {
        newState = (vy < 0 ? AnimState::Jump : AnimState::Fall);
    }
    if (m_animation.getCurrentState() != newState) {
        m_animation.setAnimation(newState);
    }
    m_animation.update(dt);
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
// Returns if the player is currently moving
bool Player::isMoving() const { return m_isMoving; }