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
    
    // Double jump variables
    bool canDoubleJump;         // Whether the player can perform a double jump
    bool hasDoubleJumped;       // Whether the player has already used their double jump
    float doubleJumpForce;      // Force of the double jump (can be different from regular jump)

public:
    Movement();
    ~Movement();

    // Action
    void jump();
    void doubleJump();
    void update(float dirX, float dt);
    // Setters
    void setOnGround(bool onGround);
    void setVelocity(float vx, float vy);
    // Getters
    bool getOnGround() const;
    bool getCanDoubleJump() const;
    bool getHasDoubleJumped() const;
    float getVelocityX() const;
    float getVelocityY() const;
};
#endif