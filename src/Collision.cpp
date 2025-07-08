#include "Collision.h"

Collision::Collision() : posX(0), posY(0), width(0), height(0), shape(CollisionShape::Rectangle) {}
Collision::Collision(float x, float y, float w, float h, CollisionShape shape)
    : posX(x), posY(y), width(w), height(h), shape(shape) {}
Collision::~Collision() {}

void Collision::setPosition(float x, float y) {
    posX = x;
    posY = y;
}

void Collision::setSize(float w, float h) {
    width = w;
    height = h;
}

bool Collision::checkCollision(const Collision& other) const {
    if (shape == CollisionShape::Rectangle && other.shape == CollisionShape::Rectangle) {
        return posX < other.posX + other.width &&
               posX + width > other.posX &&
               posY < other.posY + other.height &&
               posY + height > other.posY;
    }
    // Można dodać obsługę innych kształtów
    return false;
}

float Collision::getX() const { return posX; }
float Collision::getY() const { return posY; }
float Collision::getWidth() const { return width; }
float Collision::getHeight() const { return height; }
CollisionShape Collision::getShape() const { return shape; }