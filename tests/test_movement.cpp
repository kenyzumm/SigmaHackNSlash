#include "test_framework.h"
#include "Movement.h"

class MovementTest : public TestFixture {
protected:
    Movement movement;
    
    void SetUp() override {
        // Reset movement state before each test
        movement = Movement();
    }
};

// Test basic initialization
TEST_F(MovementTest, Initialization) {
    ASSERT_FLOAT_EQ(movement.getVelocityX(), 0.0f);
    ASSERT_FLOAT_EQ(movement.getVelocityY(), 0.0f);
    ASSERT_FALSE(movement.getOnGround());
    ASSERT_TRUE(movement.getCanDoubleJump());
    ASSERT_FALSE(movement.getHasDoubleJumped());
    ASSERT_FALSE(movement.getIsDashing());
    ASSERT_TRUE(movement.canDash());
}

// Test horizontal movement
TEST_F(MovementTest, HorizontalMovement) {
    // Test right movement
    movement.update(1.0f, 0.016f); // 60 FPS frame
    ASSERT_GT(movement.getVelocityX(), 0.0f);
    
    // Test left movement
    movement.setVelocity(0, 0);
    movement.update(-1.0f, 0.016f);
    ASSERT_LT(movement.getVelocityX(), 0.0f);
    
    // Test no movement (friction)
    movement.setVelocity(100.0f, 0);
    movement.update(0.0f, 0.016f);
    ASSERT_LT(movement.getVelocityX(), 100.0f); // Should be reduced by friction
}

// Test gravity
TEST_F(MovementTest, Gravity) {
    movement.setOnGround(false);
    movement.update(0.0f, 0.016f);
    ASSERT_GT(movement.getVelocityY(), 0.0f); // Should be falling
}

// Test jump mechanics
TEST_F(MovementTest, JumpMechanics) {
    // Set on ground
    movement.setOnGround(true);
    ASSERT_TRUE(movement.getOnGround());
    
    // Perform jump
    movement.jump();
    ASSERT_FALSE(movement.getOnGround());
    ASSERT_LT(movement.getVelocityY(), 0.0f); // Should be moving up
    ASSERT_FALSE(movement.getHasDoubleJumped()); // Double jump should be available
}

// Test double jump mechanics
TEST_F(MovementTest, DoubleJumpMechanics) {
    // First jump
    movement.setOnGround(true);
    movement.jump();
    ASSERT_FALSE(movement.getHasDoubleJumped());
    
    // Double jump
    movement.doubleJump();
    ASSERT_TRUE(movement.getHasDoubleJumped());
    ASSERT_LT(movement.getVelocityY(), 0.0f); // Should still be moving up
}

// Test double jump reset on landing
TEST_F(MovementTest, DoubleJumpReset) {
    // Jump and double jump
    movement.setOnGround(true);
    movement.jump();
    movement.doubleJump();
    ASSERT_TRUE(movement.getHasDoubleJumped());
    
    // Land on ground
    movement.setOnGround(true);
    ASSERT_FALSE(movement.getHasDoubleJumped()); // Should reset
}

// Test dash mechanics
TEST_F(MovementTest, DashMechanics) {
    // Start dash
    movement.startDash(1); // Right dash
    ASSERT_TRUE(movement.getIsDashing());
    ASSERT_FALSE(movement.canDash()); // Should not be able to dash again immediately
    
    // Check dash velocity
    ASSERT_GT(movement.getVelocityX(), 0.0f);
    ASSERT_FLOAT_EQ(movement.getVelocityY(), 0.0f); // Should cancel vertical movement
}

// Test dash cooldown
TEST_F(MovementTest, DashCooldown) {
    // First dash
    movement.startDash(1);
    ASSERT_TRUE(movement.getIsDashing());
    
    // Try to dash again immediately
    movement.startDash(-1);
    ASSERT_TRUE(movement.getIsDashing()); // Should still be dashing in original direction
    
    // Simulate dash ending
    for (int i = 0; i < 10; ++i) {
        movement.update(0.0f, 0.016f);
    }
    
    // Should not be able to dash due to cooldown
    ASSERT_FALSE(movement.canDash());
}

// Test dash direction
TEST_F(MovementTest, DashDirection) {
    // Right dash
    movement.startDash(1);
    ASSERT_GT(movement.getVelocityX(), 0.0f);
    
    // Reset and left dash
    movement = Movement();
    movement.startDash(-1);
    ASSERT_LT(movement.getVelocityX(), 0.0f);
}

// Test invalid dash
TEST_F(MovementTest, InvalidDash) {
    // Try to dash with direction 0
    movement.startDash(0);
    ASSERT_FALSE(movement.getIsDashing());
    
    // Try to dash while already dashing
    movement.startDash(1);
    ASSERT_TRUE(movement.getIsDashing());
    movement.startDash(-1);
    ASSERT_TRUE(movement.getIsDashing()); // Should still be dashing in original direction
}

// Test velocity limits
TEST_F(MovementTest, VelocityLimits) {
    // Set very high velocity
    movement.setVelocity(1000.0f, 1000.0f);
    movement.update(0.0f, 0.016f);
    
    // Should be clamped to max velocity
    ASSERT_LE(std::abs(movement.getVelocityX()), 300.0f);
    ASSERT_LE(std::abs(movement.getVelocityY()), 300.0f);
}

// Test ground state changes
TEST_F(MovementTest, GroundStateChanges) {
    // Start in air
    movement.setOnGround(false);
    ASSERT_FALSE(movement.getOnGround());
    
    // Land on ground
    movement.setOnGround(true);
    ASSERT_TRUE(movement.getOnGround());
    ASSERT_FALSE(movement.getHasDoubleJumped()); // Should reset double jump
} 