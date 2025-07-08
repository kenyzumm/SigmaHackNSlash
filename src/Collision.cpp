#include "Collision.h"

// Default constructor: sets default values (rectangle at point 0,0)
Collision::Collision() : posX(0), posY(0), width(0), height(0), shape(CollisionShape::Rectangle) {}
// Constructor with parameters: sets position, size and collision shape
Collision::Collision(float x, float y, float w, float h, CollisionShape shape)
    : posX(x), posY(y), width(w), height(h), shape(shape) {}
Collision::~Collision() {}

// Sets the position of the top-left corner of the collision
void Collision::setPosition(float x, float y) {
    posX = x;
    posY = y;
}

// Sets the size of the collision
void Collision::setSize(float w, float h) {
    width = w;
    height = h;
}

// Checks collision with another object (rectangle-rectangle)
bool Collision::checkCollision(const Collision& other) const {
    if (shape == CollisionShape::Rectangle && other.shape == CollisionShape::Rectangle) {
        return posX < other.posX + other.width &&
               posX + width > other.posX &&
               posY < other.posY + other.height &&
               posY + height > other.posY;
    }
    // Add handling for other shapes
    return false;
}

// Returns the X position of the top-left corner
float Collision::getX() const { return posX; }
// Returns the Y position of the top-left corner
float Collision::getY() const { return posY; }
// Returns the width of the collision
float Collision::getWidth() const { return width; }
// Returns the height of the collision
float Collision::getHeight() const { return height; }
// Returns the type of collision shape
CollisionShape Collision::getShape() const { return shape; }