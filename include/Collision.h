#ifndef COLLISION_H
#define COLLISION_H
#include "Game.h"

enum class CollisionShape { Rectangle, Circle };

class Collision {
public:
    float posX, posY;
    float width, height;
    CollisionShape shape;

    Collision();
    Collision(float x, float y, float w, float h, CollisionShape shape = CollisionShape::Rectangle);
    ~Collision();

    void setPosition(float x, float y);
    void setSize(float w, float h);
    bool checkCollision(const Collision& other) const;
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    CollisionShape getShape() const;
};

#endif
