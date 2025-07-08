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
    // Updates velocity based on input, gravity, and friction
    void update(float dirX, float dt);
    // Performs a jump if the player is on the ground
    void jump();
    // Sets the flag indicating whether the player is on the ground
    void setOnGround(bool onGround);
    // Returns whether the player is on the ground
    bool getOnGround() const;
    // Returns velocity in the X axis
    float getVelocityX() const;
    // Returns velocity in the Y axis
    float getVelocityY() const;
    // Sets velocity directly
    void setVelocity(float vx, float vy);
};
#endif