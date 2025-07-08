#ifndef MOVEMENT_H
#define MOVEMENT_H

// Class responsible for simple player movement physics (velocity, gravity, jump)
class Movement {
    float velocityX, velocityY; // Velocity in X and Y axes
    float acceleration;         // Horizontal acceleration
    float maxVelocity;          // Maximum velocity
    float gravity;              // Gravitational constant
    float friction;             // Friction coefficient
    float jumpForce;            // Jump force
    bool isOnGround;            // Whether the player is on the ground

public:
    Movement();
    ~Movement();

    // Action
    void jump();
    void update(float dirX, float dt);
    // Setters
    void setOnGround(bool onGround);
    void setVelocity(float vx, float vy);
    // Getters
    bool getOnGround() const;
    float getVelocityX() const;
    float getVelocityY() const;
};
#endif