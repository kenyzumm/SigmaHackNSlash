#include "Movement.h"

// Constructor: sets default physics parameters
Movement::Movement()
    : velocityX(0), velocityY(0), acceleration(1000.0f), maxVelocity(300.0f), gravity(980.0f), friction(0.9f), jumpForce(400.0f), isOnGround(false) {}

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
    }
}

// Performs a jump if the player is on the ground
void Movement::jump() {
    if (isOnGround) {
        velocityY = -jumpForce;
        isOnGround = false;
    }
}

// Sets the flag indicating if the player is on the ground
void Movement::setOnGround(bool onGround) {
    isOnGround = onGround;
}

// Returns if the player is on the ground
bool Movement::getOnGround() const {
    return isOnGround;
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