#include "Movement.h"
#include <iostream>

// Constructor: sets default physics parameters
Movement::Movement()
    : velocityX(0), velocityY(0), acceleration(1000.0f), maxVelocity(300.0f), gravity(980.0f), friction(0.9f), jumpForce(400.0f), isOnGround(false),
      canDoubleJump(true), hasDoubleJumped(false), doubleJumpForce(350.0f) {}

Movement::~Movement() {}

// Updates player velocity based on input, gravity, and friction
void Movement::update(float dirX, float dt) {
    // Horizontal movement: acceleration depends on input
    velocityX += acceleration * dirX * dt;
    if (velocityX > maxVelocity) velocityX = maxVelocity;
    if (velocityX < -maxVelocity) velocityX = -maxVelocity;
    // Friction: slows down movement when no input
    velocityX *= friction;
    // Gravity: accelerates falling if not on the ground
    if (!isOnGround) {
        velocityY += gravity * dt;
        if (velocityY > maxVelocity) velocityY = maxVelocity;
        if (velocityY < -maxVelocity) velocityY = -maxVelocity;
    } else {
        velocityY = 0;
        // Reset double jump when landing on ground
        hasDoubleJumped = false;
    }
}

// Performs a jump if the player is on the ground
void Movement::jump() {
    if (isOnGround) {
        velocityY = -jumpForce;
        isOnGround = false;
        hasDoubleJumped = false; // Reset double jump flag when performing first jump
    }
}

// Performs a double jump if the player is in the air and hasn't used double jump yet
void Movement::doubleJump() {
    if (!isOnGround && !hasDoubleJumped && canDoubleJump) {
        velocityY = -doubleJumpForce;
        hasDoubleJumped = true;
    }
}

// Sets the flag indicating if the player is on the ground
void Movement::setOnGround(bool onGround) {
    isOnGround = onGround;
    // Reset double jump when landing on ground
    if (onGround) {
        hasDoubleJumped = false;
    }
}

// Returns if the player is on the ground
bool Movement::getOnGround() const {
    return isOnGround;
}

// Returns if the player can perform a double jump
bool Movement::getCanDoubleJump() const {
    return canDoubleJump;
}

// Returns if the player has already used their double jump
bool Movement::getHasDoubleJumped() const {
    return hasDoubleJumped;
}

// Returns the velocity in the X axis
float Movement::getVelocityX() const {
    return velocityX;
}

// Returns the velocity in the Y axis
float Movement::getVelocityY() const {
    return velocityY;
}

// Sets velocity directly (e.g., during collision)
void Movement::setVelocity(float vx, float vy) {
    velocityX = vx;
    velocityY = vy;
}