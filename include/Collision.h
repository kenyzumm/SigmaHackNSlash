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

    // Setters
    void setPosition(float x, float y);
    void setSize(float w, float h);

    bool checkCollision(const Collision& other) const;

    // Getters
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    CollisionShape getShape() const;
};

#endif
