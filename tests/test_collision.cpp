#include "test_framework.h"
#include "Collision.h"

class CollisionTest : public TestFixture {
protected:
    Collision collision;
    
    void SetUp() override {
        collision = Collision();
    }
};

// Test collision initialization
TEST_F(CollisionTest, Initialization) {
    ASSERT_FLOAT_EQ(collision.getX(), 0.0f);
    ASSERT_FLOAT_EQ(collision.getY(), 0.0f);
    ASSERT_FLOAT_EQ(collision.getWidth(), 0.0f);
    ASSERT_FLOAT_EQ(collision.getHeight(), 0.0f);
    ASSERT_EQ(static_cast<int>(collision.getShape()), static_cast<int>(CollisionShape::Rectangle));
}

// Test collision with parameters
TEST_F(CollisionTest, ParameterizedInitialization) {
    Collision testCollision(10.0f, 20.0f, 30.0f, 40.0f, CollisionShape::Rectangle);
    ASSERT_FLOAT_EQ(testCollision.getX(), 10.0f);
    ASSERT_FLOAT_EQ(testCollision.getY(), 20.0f);
    ASSERT_FLOAT_EQ(testCollision.getWidth(), 30.0f);
    ASSERT_FLOAT_EQ(testCollision.getHeight(), 40.0f);
}

// Test position setting
TEST_F(CollisionTest, PositionSetting) {
    collision.setPosition(15.0f, 25.0f);
    ASSERT_FLOAT_EQ(collision.getX(), 15.0f);
    ASSERT_FLOAT_EQ(collision.getY(), 25.0f);
}

// Test size setting
TEST_F(CollisionTest, SizeSetting) {
    collision.setSize(50.0f, 60.0f);
    ASSERT_FLOAT_EQ(collision.getWidth(), 50.0f);
    ASSERT_FLOAT_EQ(collision.getHeight(), 60.0f);
}

// Test collision detection
TEST_F(CollisionTest, CollisionDetection) {
    Collision rect1(0.0f, 0.0f, 10.0f, 10.0f, CollisionShape::Rectangle);
    Collision rect2(5.0f, 5.0f, 10.0f, 10.0f, CollisionShape::Rectangle);
    
    ASSERT_TRUE(rect1.checkCollision(rect2));
    ASSERT_TRUE(rect2.checkCollision(rect1));
}

// Test no collision
TEST_F(CollisionTest, NoCollision) {
    Collision rect1(0.0f, 0.0f, 10.0f, 10.0f, CollisionShape::Rectangle);
    Collision rect2(20.0f, 20.0f, 10.0f, 10.0f, CollisionShape::Rectangle);
    
    ASSERT_FALSE(rect1.checkCollision(rect2));
    ASSERT_FALSE(rect2.checkCollision(rect1));
}

// Test edge collision
TEST_F(CollisionTest, EdgeCollision) {
    Collision rect1(0.0f, 0.0f, 10.0f, 10.0f, CollisionShape::Rectangle);
    Collision rect2(10.0f, 0.0f, 10.0f, 10.0f, CollisionShape::Rectangle);
    
    ASSERT_FALSE(rect1.checkCollision(rect2)); // Touching edges don't collide
}

// Test corner collision
TEST_F(CollisionTest, CornerCollision) {
    Collision rect1(0.0f, 0.0f, 10.0f, 10.0f, CollisionShape::Rectangle);
    Collision rect2(10.0f, 10.0f, 10.0f, 10.0f, CollisionShape::Rectangle);
    
    ASSERT_FALSE(rect1.checkCollision(rect2)); // Touching corners don't collide
} 