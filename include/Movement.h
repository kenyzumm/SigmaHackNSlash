#ifndef MOVEMENT_H
#define MOVEMENT_H

class Movement {
private:
    float velocityX, velocityY;
    float acceleration;
    float maxVelocity;
    float gravity;
    float friction;
    float mass;
    float jumpForce;
    bool isOnGround;

public:
    Movement();
    ~Movement();
    void move(float dirX, float dirY, float dt);
    void update(float dt);
    void applyGravity(float dt);
    void jump();
    void setOnGround(bool onGround);
    bool getOnGround() const;
    float getVelocityX() const;
    float getVelocityY() const;
    void setVelocity(float vx, float vy);
};
#endif