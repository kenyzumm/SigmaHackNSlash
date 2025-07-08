#include "Movement.h"

Movement::Movement()
    : velocityX(0), velocityY(0), acceleration(1000.0f), maxVelocity(300.0f), gravity(980.0f), friction(0.9f), mass(1.0f), jumpForce(400.0f), isOnGround(false) {}

Movement::~Movement() {}

void Movement::move(float dirX, float dirY, float dt) {
    // Prosty ruch z przyspieszeniem
    velocityX += acceleration * dirX * dt;
    velocityY += acceleration * dirY * dt;
    // Ograniczenie prędkości
    if (velocityX > maxVelocity) velocityX = maxVelocity;
    if (velocityX < -maxVelocity) velocityX = -maxVelocity;
    if (velocityY > maxVelocity) velocityY = maxVelocity;
    if (velocityY < -maxVelocity) velocityY = -maxVelocity;
}

void Movement::update(float dt) {
    // Tarcie
    velocityX *= friction;
    // Grawitacja
    applyGravity(dt);
}

void Movement::applyGravity(float dt) {
    if (!isOnGround) {
        velocityY += gravity * dt;
    } else {
        velocityY = 0;
    }
}

void Movement::jump() {
    if (isOnGround) {
        velocityY = -jumpForce;
        isOnGround = false;
    }
}

void Movement::setOnGround(bool onGround) {
    isOnGround = onGround;
}

bool Movement::getOnGround() const {
    return isOnGround;
}

float Movement::getVelocityX() const {
    return velocityX;
}

float Movement::getVelocityY() const {
    return velocityY;
}

void Movement::setVelocity(float vx, float vy) {
    velocityX = vx;
    velocityY = vy;
}