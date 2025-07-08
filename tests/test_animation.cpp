#include "test_framework.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class AnimationTest : public TestFixture {
protected:
    sf::Texture texture;
    sf::Sprite testSprite;
    Animation animation;
    
    AnimationTest() : testSprite(texture) {}
    
    void SetUp() override {
        animation = Animation();
        // testSprite is already constructed with texture
    }
};

// Test animation initialization
TEST_F(AnimationTest, Initialization) {
    ASSERT_NO_THROW(Animation());
}

// Test frame data setting
TEST_F(AnimationTest, FrameDataSetting) {
    ASSERT_NO_THROW(animation.setFrameData(64, 64, 0, 0));
}

// Test animation adding
TEST_F(AnimationTest, AnimationAdding) {
    animation.setFrameData(64, 64, 0, 0);
    ASSERT_NO_THROW(animation.addAnimation(AnimState::Idle, 2, 0, 0, 1.0f, 9));
}

// Test animation setting
TEST_F(AnimationTest, AnimationSetting) {
    animation.setFrameData(64, 64, 0, 0);
    animation.addAnimation(AnimState::Idle, 2, 0, 0, 1.0f, 9);
    ASSERT_NO_THROW(animation.setAnimation(AnimState::Idle));
}

// Test animation updating
TEST_F(AnimationTest, AnimationUpdating) {
    animation.setFrameData(64, 64, 0, 0);
    animation.addAnimation(AnimState::Idle, 2, 0, 0, 1.0f, 9);
    animation.setAnimation(AnimState::Idle);
    ASSERT_NO_THROW(animation.update(0.016f));
}

// Test sprite setting
TEST_F(AnimationTest, SpriteSetting) {
    ASSERT_NO_THROW(animation.setSprite(&testSprite));
}

// Test current state getting
TEST_F(AnimationTest, CurrentStateGetting) {
    animation.setFrameData(64, 64, 0, 0);
    animation.addAnimation(AnimState::Idle, 2, 0, 0, 1.0f, 9);
    animation.setAnimation(AnimState::Idle);
    ASSERT_EQ(static_cast<int>(animation.getCurrentState()), static_cast<int>(AnimState::Idle));
} 