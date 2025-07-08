#ifndef COLLISION_H
#define COLLISION_H
#include "Game.h"

// Types of shapes for collision detection
enum class CollisionShape { Rectangle, Circle };

// Class for handling simple collision between rectangles or circles
class Collision {
public:
    float posX, posY;      // Position of the top-left corner of the collision
    float width, height;   // Size of the collision
    CollisionShape shape;  // Shape of the collision

    Collision();
    Collision(float x, float y, float w, float h, CollisionShape shape = CollisionShape::Rectangle);
    ~Collision();

    // Sets the position of the collision
    void setPosition(float x, float y);
    // Sets the size of the collision
    void setSize(float w, float h);
    // Checks collision with another object
    bool checkCollision(const Collision& other) const;
    // Returns X position
    float getX() const;
    // Returns Y position
    float getY() const;
    // Returns width
    float getWidth() const;
    // Returns height
    float getHeight() const;
    // Returns shape type
    CollisionShape getShape() const;
};

#endif
